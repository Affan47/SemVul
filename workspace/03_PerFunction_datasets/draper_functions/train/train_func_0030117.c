WriteToBuffer(uint32 transize, byte* data, uint64 start, uint64 end, Requested_Block_Struct *block, const CUpDownClient* client)
{

	transferred += transize;


	uint32 lenData = (uint32) (end - start + 1);

	if(lenData > transize) {
		m_iGainDueToCompression += lenData-transize;
	}


	if (IsComplete(start, end)) {
		AddDebugLogLineN(logPartFile,
			CFormat(wxT("File '%s' has already been written from %u to %u"))
				% GetFileName() % start % end);
		return 0;
	}


	const uint64 nStartChunk = start / PARTSIZE;
	const uint64 nEndChunk = end / PARTSIZE;
	if (IsComplete(nStartChunk)) {
		AddDebugLogLineN(logPartFile, CFormat(wxT("Received data touches already hashed chunk - ignored (start): %u-%u; File=%s")) % start % end % GetFileName());
		return 0;
	} else if (nStartChunk != nEndChunk) {
		if (IsComplete(nEndChunk)) {
			AddDebugLogLineN(logPartFile, CFormat(wxT("Received data touches already hashed chunk - ignored (end): %u-%u; File=%s")) % start % end % GetFileName());
			return 0;
		} else {
			AddDebugLogLineN(logPartFile, CFormat(wxT("Received data crosses chunk boundaries: %u-%u; File=%s")) % start % end % GetFileName());
		}
	}


	m_CorruptionBlackBox->TransferredData(start, end, client->GetIP());


	PartFileBufferedData *item = new PartFileBufferedData(m_hpartfile, data, start, end, block);


	bool added = false;

	std::list<PartFileBufferedData*>::iterator it = m_BufferedData_list.begin();
	for (; it != m_BufferedData_list.end(); ++it) {
		PartFileBufferedData* queueItem = *it;

		if (item->end <= queueItem->end) {
			if (it != m_BufferedData_list.begin()) {
				added = true;

				m_BufferedData_list.insert(--it, item);
			}

			break;
		}
	}

	if (!added) {
		m_BufferedData_list.push_front(item);
	}


	m_nTotalBufferData += lenData;


	FillGap(item->start, item->end);


	std::list<Requested_Block_Struct*>::iterator it2 = m_requestedblocks_list.begin();
	for (; it2 != m_requestedblocks_list.end(); ++it2) {
		if (*it2 == item->block) {
			item->block->transferred += lenData;
		}
	}

	if (m_gaplist.IsComplete()) {
		FlushBuffer();
	}


	return lenData;
}

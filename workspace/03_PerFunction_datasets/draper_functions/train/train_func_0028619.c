ProcessResultNotes(const CUInt128& answer, TagPtrList *info)
{


	CEntry* entry = new CEntry();
	entry->m_uKeyID.SetValue(m_target);
	entry->m_uSourceID.SetValue(answer);

	bool bFilterComment = false;


	for (TagPtrList::iterator it = info->begin(); it != info->end(); ++it) {
		CTag *tag = *it;
		if (!tag->GetName().Cmp(TAG_SOURCEIP)) {
			entry->m_uIP = tag->GetInt();
		} else if (!tag->GetName().Cmp(TAG_SOURCEPORT)) {
			entry->m_uTCPport = tag->GetInt();
		} else if (!tag->GetName().Cmp(TAG_FILENAME)) {
			entry->SetFileName(tag->GetStr());
		} else if (!tag->GetName().Cmp(TAG_DESCRIPTION)) {
			wxString strComment(tag->GetStr());
			bFilterComment = thePrefs::IsMessageFiltered(strComment);
			entry->AddTag(tag);
			*it = NULL;
		} else if (!tag->GetName().Cmp(TAG_FILERATING)) {
			entry->AddTag(tag);
			*it = NULL;
		}
	}

	if (bFilterComment) {
		delete entry;
		return;
	}

	uint8_t fileid[16];
	m_target.ToByteArray(fileid);
	const CMD4Hash fileHash(fileid);


	CKnownFile* file = theApp->sharedfiles->GetFileByID(fileHash);

	if (!file) {

		file = (CKnownFile*)theApp->downloadqueue->GetFileByID(fileHash);
	}


	if (file) {
		file->AddNote(entry);
		m_answers++;
	} else {
		AddDebugLogLineN(logKadSearch, wxT("Comment received for unknown file"));
		delete entry;
	}
}

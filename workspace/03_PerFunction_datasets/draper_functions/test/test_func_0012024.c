ClearDownloadBlockRequests()
{
	{
		std::list<Requested_Block_Struct*>::iterator it = m_DownloadBlocks_list.begin();
		for (; it != m_DownloadBlocks_list.end(); ++it) {
			Requested_Block_Struct* cur_block = *it;


			if (!cur_block) continue;

			if (m_reqfile){
				m_reqfile->RemoveBlockFromList(cur_block->StartOffset, cur_block->EndOffset);
			}

			delete cur_block;
		}

		m_DownloadBlocks_list.clear();
	}

	{
		std::list<Pending_Block_Struct*>::iterator it = m_PendingBlocks_list.begin();
		for (; it != m_PendingBlocks_list.end(); ++it) {
			Pending_Block_Struct* pending = *it;

			if (!pending) continue;

			if (pending->block) {

			if (m_reqfile) {
				m_reqfile->RemoveBlockFromList(pending->block->StartOffset, pending->block->EndOffset);
			}

			delete pending->block;

			}


			if (pending->zStream){
				inflateEnd(pending->zStream);
				delete pending->zStream;
			}

			delete pending;
		}

		m_PendingBlocks_list.clear();
	}
}

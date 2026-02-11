RemoveAllSources(bool bTryToSwap)
{
	for( SourceSet::iterator it = m_SrcList.begin(); it != m_SrcList.end();) {
		CUpDownClient* cur_src = it++->GetClient();
		if (bTryToSwap) {
			if (!cur_src->SwapToAnotherFile(true, true, true, NULL)) {
				RemoveSource(cur_src,true,false);

			}
		} else {
			RemoveSource(cur_src,true,false);
		}
	}

	UpdatePartsInfo();


	if(!m_A4AFsrclist.empty()) {
		for( SourceSet::iterator it = m_A4AFsrclist.begin(); it != m_A4AFsrclist.end(); ) {
			CUpDownClient* cur_src = it++->GetClient();
			if ( cur_src->DeleteFileRequest( this ) ) {
				Notify_SourceCtrlRemoveSource(cur_src->ECID(), this);
			}
		}
		m_A4AFsrclist.clear();
	}

	m_AduSrcList_size = 0;


	UpdateFileRatingCommentAvail();
}

AddSource(CKnownFile* owner, const CClientRef& source, SourceItemType type)
{
	wxCHECK_RET(owner, wxT("NULL owner in CGenericClientListCtrl::AddSource"));
	wxCHECK_RET(source.IsLinked(), wxT("Unlinked source in CGenericClientListCtrl::AddSource"));


	bool bFound = false;
	ListIteratorPair rangeIt = m_ListItems.equal_range(source.ECID());
	for ( ListItems::iterator it = rangeIt.first; it != rangeIt.second; ++it ) {
		ClientCtrlItem_Struct* cur_item = it->second;


		if ( cur_item->GetOwner() == owner ) {

			if ((type == A4AF_SOURCE) &&
				cur_item->GetSource().GetRequestFile()
				&& std::binary_search(m_knownfiles.begin(), m_knownfiles.end(), cur_item->GetSource().GetRequestFile())) {
				cur_item->SetContents(owner, source, AVAILABLE_SOURCE);
			} else {
				cur_item->SetContents(owner, source, type);
			}
			cur_item->dwUpdated = 0;
			bFound = true;
		} else if ( type == AVAILABLE_SOURCE ) {

			cur_item->SetContents(cur_item->GetOwner(), source, A4AF_SOURCE);
			cur_item->dwUpdated = 0;
		}
	}

	if ( bFound ) {
		return;
	}

	if ( std::binary_search(m_knownfiles.begin(), m_knownfiles.end(), owner) ) {
		RawAddSource(owner, source, type);

		ShowSourcesCount( 1 );
	}
}

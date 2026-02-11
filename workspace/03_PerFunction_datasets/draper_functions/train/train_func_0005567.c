UpdateJobInfo(ConvertInfo& info)
{
	if (s_convertgui) {

		long itemnr = s_convertgui->m_joblist->FindItem(-1, info.id);

		if (itemnr == -1) {
			itemnr = s_convertgui->m_joblist->InsertItem(s_convertgui->m_joblist->GetItemCount(), info.folder.GetPrintable());
			if (itemnr != -1) {
				s_convertgui->m_joblist->SetItemData(itemnr, info.id);
			}
		}

		if (itemnr != -1) {
			s_convertgui->m_joblist->SetItem(itemnr, 0, info.filename.IsOk() ? info.folder.GetPrintable() : info.filename.GetPrintable() );
			s_convertgui->m_joblist->SetItem(itemnr, 1, GetConversionState(info.state) );
			if (info.size > 0) {
				s_convertgui->m_joblist->SetItem(itemnr, 2, CFormat(_("%s (Disk: %s)")) % CastItoXBytes(info.size) % CastItoXBytes(info.spaceneeded));
			} else {
				s_convertgui->m_joblist->SetItem(itemnr, 2, wxEmptyString);
			}
			s_convertgui->m_joblist->SetItem(itemnr, 3, info.filehash);
		}
	}
}

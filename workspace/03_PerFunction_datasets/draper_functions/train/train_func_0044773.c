OnAddCollection( wxCommandEvent& WXUNUSED(evt) )
{
	int item = GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
	if (item != -1) {


#if 0
		CKnownFile *file = (CKnownFile*)GetItemData(item);
#else
		CKnownFile *file = reinterpret_cast<CKnownFile*>(GetItemData(item));
#endif

		wxString CollectionFile = file->GetFilePath().JoinPaths(file->GetFileName()).GetRaw();
		CMuleCollection my_collection;
		if (my_collection.Open( (std::string)CollectionFile.mb_str() )) {

			for (size_t e = 0; e < my_collection.GetFileCount(); ++e) {
				theApp->downloadqueue->AddLink(
					wxString(my_collection.GetEd2kLink(e).c_str(), wxConvUTF8));
			}

		}
	}
}

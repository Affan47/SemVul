ShowFile( CPartFile* file, bool show )
{
	wxASSERT( file );

	ListItems::iterator it = m_ListItems.find( file );

	if ( it != m_ListItems.end() ) {
		FileCtrlItem_Struct* item = it->second;

		if ( show ) {

			long index = FindItem( -1, reinterpret_cast<wxUIntPtr>(item) );
			if ( index == -1 ) {
				long newitem = InsertItem( GetItemCount(), wxEmptyString );

				SetItemPtrData( newitem, reinterpret_cast<wxUIntPtr>(item) );

				wxListItem myitem;
				myitem.m_itemId = newitem;
				myitem.SetBackgroundColour( GetBackgroundColour() );

				SetItem(myitem);

				RefreshItem( newitem );

				ShowFilesCount( 1 );
			}
		} else {

			long index = FindItem( -1, reinterpret_cast<wxUIntPtr>(item) );
			if ( index > -1 ) {
				DeleteItem( index );
				ShowFilesCount( -1 );
			}
		}
	}
}

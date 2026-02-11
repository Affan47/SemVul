OnRightDown( wxMouseEvent& evt )
{

	if ( FindFocus() != this )
		SetFocus();

	wxMenu popup_menu;

	popup_menu.Append( CMTCE_Cut, _("Cut") );
	popup_menu.Append( CMTCE_Copy, _("Copy") );
	popup_menu.Append( CMTCE_Paste, _("Paste") );
	popup_menu.Append( CMTCE_Clear, _("Clear") );

	popup_menu.AppendSeparator();

	popup_menu.Append( CMTCE_SelAll, _("Select All") );


	bool canpaste = false;
	if ( CanPaste() ) {
		if ( wxTheClipboard->Open() ) {
			if ( wxTheClipboard->IsSupported( wxDF_TEXT ) ) {
				wxTextDataObject data;
	 			wxTheClipboard->GetData( data );

				canpaste = (data.GetTextLength() > 0);
			}
			wxTheClipboard->Close();
		}
	}


	popup_menu.Enable( CMTCE_Paste,		canpaste );
	popup_menu.Enable( CMTCE_Clear,		IsEditable() && !GetValue().IsEmpty() );

	PopupMenu( &popup_menu, evt.GetX(), evt.GetY() );
}

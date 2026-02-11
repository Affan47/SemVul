OnNMRclickDLtab(wxMouseEvent& evt)
{

	if ( evt.GetEventObject() != (wxObject*)m_dlTab )
		return;

	if ( m_dlTab->GetSelection() == -1 ) {
		return;
	}


	if ( m_menu == NULL ) {
		m_menu = new wxMenu( _("Category") );

		if ( m_dlTab->GetSelection() == 0 ) {
			wxMenu* catmenu = new wxMenu();

			catmenu->Append( MP_CAT_SET0,      _("All") );
			catmenu->Append( MP_CAT_SET0 + 1,  _("All others") );

			catmenu->AppendSeparator();

			catmenu->Append( MP_CAT_SET0 + 2,  _("Incomplete") );
			catmenu->Append( MP_CAT_SET0 + 3,  _("Completed") );
			catmenu->Append( MP_CAT_SET0 + 4,  _("Waiting") );
			catmenu->Append( MP_CAT_SET0 + 5,  _("Downloading") );
			catmenu->Append( MP_CAT_SET0 + 6,  _("Erroneous") );
			catmenu->Append( MP_CAT_SET0 + 7,  _("Paused") );
			catmenu->Append( MP_CAT_SET0 + 8,  _("Stopped") );
			catmenu->Append( MP_CAT_SET0 + 15, _("Active") );

			catmenu->AppendSeparator();

			catmenu->Append( MP_CAT_SET0 + 9,  _("Video") );
			catmenu->Append( MP_CAT_SET0 + 10, _("Audio") );
			catmenu->Append( MP_CAT_SET0 + 11, _("Archive") );
			catmenu->Append( MP_CAT_SET0 + 12, _("CD-Images") );
			catmenu->Append( MP_CAT_SET0 + 13, _("Pictures") );
			catmenu->Append( MP_CAT_SET0 + 14, _("Text") );

			m_menu->Append(0, _("Select view filter"), catmenu);
		}

		m_menu->Append( MP_CAT_ADD, _("Add category") );

		if ( m_dlTab->GetSelection() ) {
			m_menu->Append(MP_CAT_EDIT,_("Edit category"));
			m_menu->Append(MP_CAT_REMOVE, _("Remove category"));
		}

		m_menu->AppendSeparator();

		m_menu->Append( MP_CANCEL, _("Cancel"));
		m_menu->Append( MP_STOP,   _("&Stop"));
		m_menu->Append( MP_PAUSE,  _("&Pause"));
		m_menu->Append( MP_RESUME, _("&Resume"));

		PopupMenu(m_menu, evt.GetPosition());

		delete m_menu;
		m_menu = NULL;
	}
}

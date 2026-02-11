PreferencesDebug( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxCheckBox *item1 = new wxCheckBox( parent, ID_VERBOSEDEBUG, _("Enable Verbose Debug-Logging."), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxStaticBox *item3 = new wxStaticBox( parent, -1, _("Message Categories:") );
    wxStaticBoxSizer *item2 = new wxStaticBoxSizer( item3, wxVERTICAL );

    wxWindow *item4 = new wxCheckListBox( parent, ID_DEBUGCATS );
    wxASSERT( item4 );
    item2->Add( item4, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item0->Add( item2, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }

    return item0;
}

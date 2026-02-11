sharedfilesTopDlg( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxFlexGridSizer *item1 = new wxFlexGridSizer( 4, 0, 0 );
    item1->AddGrowableCol( 1 );

    wxStaticText *item2 = new wxStaticText( parent, -1, _("Shared files"), wxDefaultPosition, wxDefaultSize, 0 );
    item2->SetName( wxT("sharedFilesLabel") );
    item1->Add( item2, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );

    wxString strs3[] =
    {
        _("All files"),
        _("Selected files"),
        _("Active uploads only")
    };
    wxRadioBox *item3 = new wxRadioBox( parent, ID_SHOW_CLIENTS_MODE, _("Show Clients for"), wxDefaultPosition, wxDefaultSize, 3, strs3, 1, wxNO_BORDER|wxRA_SPECIFY_ROWS );
    item1->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticText *item4 = new wxStaticText( parent, -1, _("Reload:"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->SetName( wxT("sharedFilesLabel") );
    item1->Add( item4, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );

    wxBitmapButton *item5 = new wxBitmapButton( parent, ID_BTNRELSHARED, amuleDlgImages( 18 ), wxDefaultPosition, wxSize(32,32) );
    item5->SetToolTip( _("Reload your shared files") );
    item1->Add( item5, 0, wxALIGN_CENTER_VERTICAL, 0 );

    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 0 );

    CSharedFilesCtrl *item6 = new CSharedFilesCtrl( parent, ID_SHFILELIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxSUNKEN_BORDER );
    item6->SetName( wxT("sharedFilesCt") );
    item0->Add( item6, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }

    return item0;
}

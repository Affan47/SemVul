PreferencesDirectoriesTab( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxStaticBox *item2 = new wxStaticBox( parent, -1, _("Destination folder for downloads") );
    wxStaticBoxSizer *item1 = new wxStaticBoxSizer( item2, wxHORIZONTAL );

    CMuleTextCtrl *item3 = new CMuleTextCtrl( parent, IDC_INCFILES, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item1->Add( item3, 1, wxGROW|wxALIGN_CENTER_HORIZONTAL, 5 );

    wxButton *item4 = new wxButton( parent, IDC_SELINCDIR, _("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item4, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL, 5 );

    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxStaticBox *item6 = new wxStaticBox( parent, -1, _("Folder for temporary download files") );
    wxStaticBoxSizer *item5 = new wxStaticBoxSizer( item6, wxHORIZONTAL );

    CMuleTextCtrl *item7 = new CMuleTextCtrl( parent, IDC_TEMPFILES, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item5->Add( item7, 1, wxGROW|wxALIGN_CENTER_HORIZONTAL, 5 );

    wxButton *item8 = new wxButton( parent, IDC_SELTEMPDIR, _("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item8, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL, 5 );

    item0->Add( item5, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxStaticBox *item10 = new wxStaticBox( parent, -1, _("Shared folders") );
    wxStaticBoxSizer *item9 = new wxStaticBoxSizer( item10, wxVERTICAL );

    wxStaticText *item11 = new wxStaticText( parent, -1, _("(Right click on folder icon for recursive share)"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    item9->Add( item11, 0, wxALIGN_CENTER, 0 );

    CDirectoryTreeCtrl *item12 = new CDirectoryTreeCtrl(parent, IDC_SHARESELECTOR, wxPoint(0,0), wxSize(100,100), wxSUNKEN_BORDER|wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT );
    wxASSERT( item12 );
    item9->Add( item12, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxCheckBox *item13 = new wxCheckBox( parent, IDC_SHAREHIDDENFILES, _("Share hidden files"), wxDefaultPosition, wxDefaultSize, 0 );
    item13->SetValue( TRUE );
    item9->Add( item13, 0, wxALIGN_CENTER_VERTICAL, 0 );

    item0->Add( item9, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }

    return item0;
}

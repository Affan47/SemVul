AddStaticLine(wxBoxSizer *mainColumn)
{
#if wxUSE_STATLINE
    mainColumn->Add(
        new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(495, -1)),
        0,
        wxEXPAND | wxALL,
        5
    );
    mainColumn->Add(0,5,
        0,
        wxEXPAND
    );
#else
    (void)mainColumn;
#endif
}

Add( const wxString& label, const wxBitmap& bitmap, int value )
{
    EnsureData();

    wxPGChoiceEntry* p = new wxPGChoiceEntry(label, value);
    p->SetBitmap(bitmap);
    m_data->Insert( -1, p );
    return *p;
}

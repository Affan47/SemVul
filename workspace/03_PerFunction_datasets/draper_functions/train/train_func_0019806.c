OnCreateStatusBar(int number, long style, wxWindowID id, const wxString& name)
{
    cbStatusBar* sb = new cbStatusBar(this, id, style, name);
    sb->SetFieldsCount(number);

    return sb;
}

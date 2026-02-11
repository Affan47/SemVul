AddPagePrivate(wxWindow* p, const wxString& title, wxBitmap* icon)
{
    const wxBitmap& bmp = icon ? *icon : m_DefaultBitmap;

    AddPage(p, title, false, bmp);
    return GetPageCount() - 1;
}

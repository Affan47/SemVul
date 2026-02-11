CanOpen(const wxString& location)
{
    if (b_ShuttingDown) return false;


    return false;


    wxString p = GetProtocol(location);
    if ((p == wxT("http")) || (p == wxT("ftp")))
    {
        wxURL url(p + wxT(":") + StripProtocolAnchor(location));
        return (url.GetError() == wxURL_NOERR);
    }
    return false;
}

ConvertLinkToWebsiteIndex(const wxString& strLink, wxInt32& iProjectIndex, wxInt32& iWebsiteIndex) {
    wxString strTemplate = strLink;
    wxString strBuffer = wxEmptyString;
    long lProjectIndex, lWebsiteIndex;

    strTemplate.Replace(wxT("web:"), wxEmptyString);

    strBuffer = strTemplate;
    strBuffer.Remove(strBuffer.Find(wxT(":")));
    strBuffer.ToLong((long*) &lProjectIndex);
    iProjectIndex = lProjectIndex;

    strBuffer = strTemplate;
    strBuffer = strBuffer.Mid(strBuffer.Find(wxT(":")) + 1);
    strBuffer.ToLong((long*) &lWebsiteIndex);
    iWebsiteIndex = lWebsiteIndex;

    return 0;
}

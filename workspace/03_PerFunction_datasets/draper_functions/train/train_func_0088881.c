IsCCToolsINI(const wxString& filename) {
    if(filename.empty())
        return false;
    std::ifstream stream(filename.mb_str());
    char headerbuf[10];
    if(!stream.read(headerbuf, 9))
        return false;
    stream.close();
    headerbuf[9] = 0;
    wxString header(headerbuf, wxConvUTF8);
    header.MakeLower();
    return header == wxT("[tileset]");
}

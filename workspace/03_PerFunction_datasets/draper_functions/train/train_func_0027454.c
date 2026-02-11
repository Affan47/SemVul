LogSearch(const wxString& file, int line, const wxString& lineText)
{
    wxArrayString values;
    wxString lineTextL;
    wxString lineStr;


    if( line != -1)
    {
        lineStr.Printf(_T("%d"), line);
    }
    else
    {
        lineStr.Printf(_T(" "));
    }
    lineTextL = lineText;
    lineTextL.Replace(_T("\t"), _T(" "));
    lineTextL.Replace(_T("\r"), _T(" "));
    lineTextL.Replace(_T("\n"), _T(" "));
    lineTextL.Trim(false);
    lineTextL.Trim(true);

    values.Add(file);
    values.Add(lineStr);
    values.Add(lineTextL);

    m_pSearchLog->Append(values, line == -1 ? Logger::caption : Logger::info);
}

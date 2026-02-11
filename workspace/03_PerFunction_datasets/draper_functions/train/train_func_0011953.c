GetOption(const wxString& name, wxArrayInt &values,
                             int count, const wxString& delims) const
{
    wxString value = GetOption(name);
    wxStringTokenizer tokens(value, delims, wxTOKEN_STRTOK);
    int read_count = 0;

    while (((count < 0) || (read_count <= count)) && tokens.HasMoreTokens())
    {
        long num;
        if (!tokens.GetNextToken().ToLong(&num)) return read_count;
        values.Add(num);
        read_count++;
    }
    return read_count;
}

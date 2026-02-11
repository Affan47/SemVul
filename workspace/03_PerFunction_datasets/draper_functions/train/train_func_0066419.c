SetFilename(const string &s)
{
    string::size_type Pos = find_last_of("\\/");

    if (Pos != string::npos)
        *this = replace(Pos + 1, string::npos, s);
    else
        *this = s;
}

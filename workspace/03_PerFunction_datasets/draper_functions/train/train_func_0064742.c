getBool(const string &name) const
{

    string val = getStr(name);
    size_t n = val.find_first_of(" \n\r\t");
    while (n != string::npos)
    {
        val = val.erase(n, 1);
        n = val.find_first_of(" \n\r\t");
    }
    return (val=="1" || cxx_strcasecmp(val.c_str() , "true")==0);
}

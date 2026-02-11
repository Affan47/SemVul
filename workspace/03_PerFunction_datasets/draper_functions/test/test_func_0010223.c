normalizePath(const string& path)
{
    string result = path;
    replace(result.begin(), result.end(), '\\', '/');
    string::size_type pos;
    while((pos = result.find("//")) != string::npos)
    {
        result.replace(pos, 2, "/");
    }
    if(result.size() > 1 && isalpha(result[0]) && result[1] == ':')
    {
        result = result.substr(2);
    }
    return result;
}

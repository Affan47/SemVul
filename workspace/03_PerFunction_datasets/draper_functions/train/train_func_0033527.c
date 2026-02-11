AddSearchPath(const char *path)
{
    std::string p;


    uint32 len = strlen(path);
    for(uint32 i = 0; i < len; i++)
    {
        if(path[i] == '\\')
            p += '/';
        else
            p += path[i];
    }

    if(p[p.size()-1] != '/')
        p += '/';
    for(std::deque<std::string>::iterator it = _paths.begin(); it != _paths.end(); it++)
    {


#if PLATFORM == PLATFORM_WIN32
        if(!stricmp(p.c_str(), it->c_str()))
            return;
#else
        if(p == *it)
            return;
#endif
    }

    _paths.push_back(p);
}

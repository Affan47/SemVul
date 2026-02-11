split_path (const string& path, string* dir_part, string* filename_part)
{
    size_t lslash = path.find_last_of (PathSeparators);
    if (
#ifdef __MINGW32__
	    lslash == 2 && path[1] == ':' && (path[0] >= 'A' && path[0] <= 'Z')
#else
	    lslash == 0
#endif
	    ) {
	return false;
    }

    if (lslash == path.length()-1)
        return split_path(path.substr(0, lslash), dir_part, filename_part);

    if (lslash == string::npos)
        return false;

    size_t lnslash = path.find_last_not_of (PathSeparators, lslash);

    if (dir_part) *dir_part           = path.substr(0, lnslash+1);
    if (filename_part) *filename_part = path.substr(lslash+1);

    return true;
}

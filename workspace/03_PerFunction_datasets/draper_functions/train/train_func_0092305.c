trim_file(const char* file)
{


    const int max_filename_len = 20;

    if (0 == file) {
        return std::string(max_filename_len, ' ');
    }


    const char * pEnd = file + strlen(file);
    while ((pEnd > file) && ('/' != *pEnd) && ('\\' != *pEnd)) {
        pEnd--;
    }
    if (pEnd != file)
        pEnd++;

    std::string result = "";
    int         i      = 0;
    for ( ;(*pEnd != '\0') && (i < max_filename_len); i++, pEnd++) {
        result += *pEnd;
    }
    for ( ; i < max_filename_len; i++) {
        result += ' ';
    }

    return result;
}

xjoin ( const std::string &path, const std::string &file ) {
    #ifdef WIN32
    const static std::string sep = "\\";
    #else
    const static std::string sep = "/";
    #endif

    if ( file.length()>0 && file.substr(0,1) == sep ) {
        return file;
    }

    if ( path.length() < 1 ) return file;

    if ( path.substr ( path.length()-1, 1 ) != sep ) return path + sep + file;
    return path + file;

}

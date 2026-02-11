unset_path(const std::string &path_base,const std::list<std::string> &tokens)
{
    if(tokens.size() < 1) return false;
    std::string dir = path_base;
    const std::list<std::string>::const_iterator itLastElement = --tokens.end();
    for (std::list<std::string>::const_iterator it = tokens.begin();
         it != itLastElement; it++) {
        dir = Glib::build_filename(dir, *it);
        if (!create_directory(dir)) return false;
    };
    std::string file = Glib::build_filename(dir, tokens.back() + ".xml");
    return (::remove(file.c_str()) == 0);
}

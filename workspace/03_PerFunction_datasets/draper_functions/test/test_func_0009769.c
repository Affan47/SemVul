resourceValue(const std::string &name, const std::string &altname) {
    XrmValue value;
    char *value_type;
    if (*m_database != 0 && XrmGetResource(*m_database, name.c_str(),
                                           altname.c_str(), &value_type, &value) && value.addr != 0)
        return string(value.addr);

    return "";
}

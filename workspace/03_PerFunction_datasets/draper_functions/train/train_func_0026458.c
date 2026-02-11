find(const string &entry, bool caseSensitive)
{
    BOOST_FOREACH(const string &e, *this) {
        if (caseSensitive ? e == entry : boost::iequals(e, entry)) {
            return m_path + "/" + e;
        }
    }
    return "";
}

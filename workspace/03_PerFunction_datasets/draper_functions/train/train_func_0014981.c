writeProperties(const ConfigProps &props)
{
    BOOST_FOREACH(const ConfigProps::value_type &entry, props) {
        setProperty(entry.first, entry.second);
    }
}

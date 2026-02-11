toFile(std::ostream &file)
{
    BOOST_FOREACH(const StringPair &prop, m_props) {
        file << prop.first << " = " <<  prop.second << std::endl;
    }
}

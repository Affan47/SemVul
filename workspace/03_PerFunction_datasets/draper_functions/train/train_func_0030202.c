read()
{
    boost::shared_ptr<std::istream> file(m_data->read());
    std::string line;
    while (std::getline(*file, line)) {
        string property, value;
        bool isComment;
        if (getContent(line, property, value, isComment, false)) {
            m_props.insert(StringPair(property, value));
        }
    }
    m_modified = false;
}

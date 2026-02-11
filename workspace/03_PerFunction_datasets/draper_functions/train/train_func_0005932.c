mapIntItem(const std::string & name, long l)
{
    m_stream << std::string(m_indent, ' ');
    m_bridge.mapIntItem(name, l);
    m_stream << std::endl;
}

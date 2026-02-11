addParam(const std::string &name, eType type,
        const std::string &help)
{
    Param param(type, help);
    m_params.insert(
                std::pair<std::string,Param>(name, param));
    int paramSize = name.size() + getType(type).size();
    if (paramSize > m_maxSize) {
        m_maxSize = paramSize;
    }
}

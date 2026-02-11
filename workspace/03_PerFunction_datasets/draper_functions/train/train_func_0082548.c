hasParameter(const char* name) const
{
    string n = name;
    int varNum = tryEncodeShapeName(n);
    if (varNum < 0) return NULL;
    std::map<int, ConfigParam*>::const_iterator elem = m_ConfigParameters.find(varNum);
    if (elem == m_ConfigParameters.end()) return NULL;
    return elem->second->second;
}

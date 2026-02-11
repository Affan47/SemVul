VariableExists(const string& inName) const
{
    for (vector<MushcoreConfig *>::const_reverse_iterator p = m_config.rbegin();
         p != m_config.rend(); ++p)
    {
        if ((*p)->Exists(inName))
        {
            return true;
        }
    }
    return false;
}

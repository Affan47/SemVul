getInt(const std::wstring &key, int dflt) const
{
    ValuesMap::const_iterator i = fields.find(key);
    return (i != fields.end()) ? ((*i).second ? (*i).second->asInt() : dflt) : dflt;
}

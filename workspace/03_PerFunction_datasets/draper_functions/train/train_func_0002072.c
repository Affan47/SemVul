addToMessage(MapType & m) const
{
    typedef MapType::const_iterator Iter;
    for (Iter I = m_attributes.begin(); I != m_attributes.end(); I++) {
        m[I->first] = I->second;
    }
}

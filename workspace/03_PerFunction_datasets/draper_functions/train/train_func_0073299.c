GetSingleCreatureGuid(uint8 event1, uint8 event2)
{
    GuidVector::const_iterator itr = m_EventObjects[MAKE_PAIR32(event1, event2)].creatures.begin();
    if (itr != m_EventObjects[MAKE_PAIR32(event1, event2)].creatures.end())
        { return *itr; }
    return ObjectGuid();
}

RemoveShortFlag(uint16 index, bool highpart, uint16 oldFlag)
{
    MANGOS_ASSERT(index < m_valuesCount || PrintIndexError(index, true));

    if (uint16(m_uint32Values[index] >> (highpart ? 16 : 0)) & oldFlag)
    {
        m_uint32Values[index] &= ~uint32(uint32(oldFlag) << (highpart ? 16 : 0));
        m_changedValues[index] = true;
        MarkForClientUpdate();
    }
}

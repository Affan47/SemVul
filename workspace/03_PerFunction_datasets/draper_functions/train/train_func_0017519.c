UpdateUInt32Value(uint16 index, uint32 value)
{
    MANGOS_ASSERT(index < m_valuesCount || PrintIndexError(index, true));

    m_uint32Values[index] = value;
    m_changedValues[index] = true;
}

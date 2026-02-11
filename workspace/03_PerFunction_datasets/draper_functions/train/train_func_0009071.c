GetFieldType(int nFieldId)
{
    if (m_pasFieldDef == NULL || nFieldId < 0 || nFieldId >= m_numFields)
        return TABFUnknown;

    return m_pasFieldDef[nFieldId].eTABType;
}

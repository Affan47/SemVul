Head()
{
    ASSERT(m_ListHead);
    ModeSet* pNew = new ModeSet(HeadPrintMode());
    return pNew;
}

SetTargetType(TargetType pt)
{
    if (m_TargetType == pt)
        return;

    m_TargetType = pt;
    m_OutputFilename = SuggestOutputFilename();
    SetModified(true);
}

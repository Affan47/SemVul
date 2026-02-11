SetTextSpacing(TABTextSpacing eSpacing)
{

    m_nTextAlignment &= ~ 0x1800;

    if (eSpacing == TABTS1_5)
        m_nTextAlignment |= 0x0800;
    else if (eSpacing == TABTSDouble)
        m_nTextAlignment |= 0x1000;
}

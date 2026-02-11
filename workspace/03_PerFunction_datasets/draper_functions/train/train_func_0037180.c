WriteBit(const bool& bit)
{
    if(bit)
#if 1

        SetBit(m_current_byte, CHAR_BIT-1-m_current_pos);
#else

        SetBit(m_current_byte, m_current_pos);
#endif

    if ( m_current_pos == CHAR_BIT-1)
    {

        OutputCurrentByte();
        m_current_byte = 0;
        m_current_pos = 0;
    }
    else

        ++m_current_pos;
}

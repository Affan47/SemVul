IsEscapedChar()
{

    if (PreviousChar() != '\\')
        return true;
    else
    {

        unsigned int numBackslash = 2;
        while (   m_TokenIndex >= numBackslash
               && ((m_TokenIndex - numBackslash) <= m_BufferLen)
               && (m_Buffer.GetChar(m_TokenIndex - numBackslash) == '\\') )
            ++numBackslash;

        if ( (numBackslash%2) == 1)
            return true;
        else
            return false;
    }
    return false;
}

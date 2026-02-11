GetMarkNext()

{
    int index = m_currIndex;
    int oldPos = m_EdPosnArray[index];
    if ( (++index) >= MaxEntries) index = 0;
    int newPos = m_EdPosnArray[index] ;

    for (int i=0; i<MaxEntries;++i)
    {
        if ((newPos != oldPos) && (newPos != -1)) break;
        if ( (++index) >= MaxEntries ) index = 0;
        newPos = m_EdPosnArray[index] ;
    }
    if (newPos == -1) return oldPos;
    m_currIndex = index;
    return newPos;
}

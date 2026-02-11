ClearMark(int startPos, int endPos)

{
        for (int i=0; i<MaxEntries; ++i)
        {
            if (( m_EdPosnArray[i] >= startPos) && (m_EdPosnArray[i] <= endPos) )
                m_EdPosnArray[i] = -1;
        }
}

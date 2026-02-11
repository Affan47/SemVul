SetRowCount(int RowCount)
{
    if( RowCount == m_RowCount )
        return;

    char** NewScreen = new char* [RowCount];
    if( RowCount > m_RowCount )
    {
        memcpy(NewScreen, m_Screen, sizeof(char**)*m_RowCount);
        for( int i = m_RowCount; i < RowCount; i++ )
                NewScreen[i] = AllocNewLine(m_ColsPerPage);
    }
    else
    {
        memcpy(NewScreen, m_Screen, sizeof(char**)*RowCount);
        for( int i = RowCount; i < m_RowCount; i++ )
                delete []m_Screen[i];
    }
    delete []m_Screen;
    m_Screen = NewScreen;
    m_RowCount = RowCount;
}

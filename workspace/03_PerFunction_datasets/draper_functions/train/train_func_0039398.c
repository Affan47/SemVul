Index( int row, int col ) const
{
    int n, count = m_blocks.GetCount();
    if ((count == 0) || !m_bounds.Contains(row, col))
        return wxNOT_FOUND;

    for (n=FindTopRow(row); n<count; n++)
    {
        if ( m_blocks[n].Contains(row, col) )
            return n;
        if (row < m_blocks[n].GetTop())
            return wxNOT_FOUND;
    }
    return wxNOT_FOUND;
}

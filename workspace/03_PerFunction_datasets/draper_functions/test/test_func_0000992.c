IsInSelection(int row, int col) const
{
    int n, count = m_blocks.GetCount();
    for (n=0; n<count; n++)
    {
        if (m_blocks[n].Contains(row, col))
            return true;
    }
    return false;
}

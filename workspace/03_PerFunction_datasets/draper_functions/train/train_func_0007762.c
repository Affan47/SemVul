IsNodeColored(void) const
{
  if ( m_Parent != ITK_NULLPTR )
    {
    const OctreeNodeBranch *colorTable = m_Parent->GetColorTable();
    const OctreeNodeBranch *first = &( colorTable[0] );
    const OctreeNodeBranch *last = &( colorTable[m_Parent->GetColorTableSize() - 1] );

    return this->m_Branch >= first && this->m_Branch <= last;
    }
  else
    {
    return false;
    }
}

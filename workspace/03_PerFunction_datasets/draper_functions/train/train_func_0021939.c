GetBlock( int index ) const
{
    wxCHECK_MSG((index>=0) && (index<int(m_blocks.GetCount())), wxEmptyBlockInt, wxT("Invalid index"));
    return m_blocks[index];
}

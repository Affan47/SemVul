InitItems( int num )
{
    for (int i = 0; i < num; i++)
        m_items.Append( new wxListItemData(m_owner) );
}

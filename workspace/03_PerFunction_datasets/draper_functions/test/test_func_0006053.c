getLastItem() const
{
	UT_uint32 i = m_pItems.getItemCount();
	if(i == 0 )
		return NULL;
	else
	{
		return m_pItems.getNthItem(i-1);
	}
}

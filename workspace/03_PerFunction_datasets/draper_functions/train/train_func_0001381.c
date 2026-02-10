ValueSort(const CStatTreeItemBase* a, const CStatTreeItemBase* b)
{
	if (a->m_id < 0x00000100 || a->m_id > 0x7fffffff || b->m_id < 0x00000100 || b->m_id > 0x7fffffff) {
		return a->m_id > b->m_id;
	} else {


#if 0
		return ((CStatTreeItemCounter*)a)->GetValue() > ((CStatTreeItemCounter*)b)->GetValue();
#else
		return dynamic_cast<const CStatTreeItemCounter*>(a)->GetValue() > dynamic_cast<const CStatTreeItemCounter*>(b)->GetValue();
#endif

	}
}

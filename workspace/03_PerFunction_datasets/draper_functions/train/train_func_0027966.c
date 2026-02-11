insertObjectBeforeFrag(pf_Frag * pF, PTObjectType pto,
										   const gchar ** attributes)
{

	UT_return_val_if_fail(pF && pF->getPrev() && pF != m_fragments.getFirst(), false);

	pf_Frag_Object * pfo = NULL;
	if(!_makeObject(pto,attributes,pfo) || !pfo)
		return false;

	if(attributes)
	{
		const gchar * pXID = UT_getAttribute(PT_XID_ATTRIBUTE_NAME, attributes);
		UT_uint32 iXID = 0;
		if(pXID && *pXID)
		{
			iXID = atoi(pXID);
			pfo->setXID(iXID);
		}
	}

	m_fragments.insertFragBefore(pF, pfo);
	return true;
}

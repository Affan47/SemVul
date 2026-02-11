getNthItemTimeT(UT_uint32 n) const
{
	UT_return_val_if_fail(m_pDoc,0);

    time_t tT = 0;
	if(n == 0)
    {
        time(&tT);
    }
    else
    {
        tT = ((AD_Revision *)(m_pDoc->getRevisions()).getNthItem(n-1))->getStartTime();
    }
	return tT;
}

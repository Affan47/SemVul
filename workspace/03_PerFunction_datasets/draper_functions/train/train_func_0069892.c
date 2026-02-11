setNextRun(fp_Run* p, bool bRefresh)
{
	if(p != m_pNext)
	{

		if(bRefresh)
			orDrawBufferDirty(GRSR_ContextSensitive);


#if 0


		if(m_pPrev && bRefresh)
		{
			m_pPrev->markDrawBufferDirty();
			m_pPrev->markWidthDirty();
		}
#endif
		m_pNext = p;
	}
}

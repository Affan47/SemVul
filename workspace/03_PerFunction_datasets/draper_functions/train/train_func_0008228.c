isValid(void) const
{
	bool b = ((m_iNumProps > 0) && (NULL != m_pszProps));
	if(m_iNumProps > 0)
	{
		UT_ASSERT(NULL != m_pszProps);
	}
	xxx_UT_DEBUGMSG(("Numprops %d m_pszProps %x \n",m_iNumProps,m_pszProps));
	return b;
}

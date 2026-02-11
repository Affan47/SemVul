isGrammarLoaded(void) const
{
	XAP_Module * pGrammar = m_pApp->getPlugin("abigrammar");
	if(pGrammar == NULL)
	{
		return false;
	}
	return true;
}

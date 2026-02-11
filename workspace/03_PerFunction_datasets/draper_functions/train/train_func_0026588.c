getActiveParent(void) const
{
	fl_AutoNum * pAutoNum = m_pParent;

	while (pAutoNum && pAutoNum->isEmpty())
		pAutoNum = pAutoNum->getParent();

	return pAutoNum;
}

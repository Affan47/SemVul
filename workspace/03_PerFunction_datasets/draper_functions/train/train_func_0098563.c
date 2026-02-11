FixFeatureTestsInRules(GrcFont * pfont)
{
	GdlRuleItem::FixFeatureTestsInRules(pfont);

	for (size_t iavs = 0; iavs < this->m_vpavs.size(); iavs++)
		m_vpavs[iavs]->FixFeatureTestsInRules(pfont);
}

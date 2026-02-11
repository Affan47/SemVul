MovePassConstraintsToRule(std::vector<GdlExpression *> & m_vpexpPassConstr)
{
	for (size_t ipexp = 0; ipexp < m_vpexpPassConstr.size(); ipexp++)
	{
		m_vpexpConstraints.push_back(m_vpexpPassConstr[ipexp]->Clone());
	}
}

isNeighbor(const TNodeID &otherArea, const THypothesisID &hyp_id ) const
{
	for (TArcList::const_iterator it=m_arcs.begin();it!=m_arcs.end();++it)
		if ((*it)->m_hypotheses.has(hyp_id) &&
			( (*it)->m_nodeFrom==otherArea || (*it)->m_nodeTo==otherArea ) )
			return true;
	return false;
}

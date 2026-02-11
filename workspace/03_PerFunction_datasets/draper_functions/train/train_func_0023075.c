getMass(int node) const
{
	return(m_nodes[node].m_im>0?1/m_nodes[node].m_im:0);
}

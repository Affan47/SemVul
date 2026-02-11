onArcDestruction(CHMHMapArc *arc)
{


	TArcList::iterator it = m_arcs.find_ptr_to(arc);
	if (it!=m_arcs.end())
		m_arcs.erase( it );
}

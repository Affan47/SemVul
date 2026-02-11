BackExtendToStrip(size_t Start, triangle_order Order, bool ClockWise)
{

	m_Triangles[Start]->SetStripID(++m_StripID);
	BackAddIndex(LastEdge(* m_Triangles[Start], Order).B());
	size_t Size = 1;

	tri_iterator Node;


	for (Node = (m_Triangles.begin() + Start);
		!Cache() || ((Size + 2) < CacheSize());
		++Size) {

		const const_link_iterator Link = BackLinkToNeighbour(Node, ClockWise, Order);


		if (Link == Node->out_end())
			break;

		else {
			Node = Link->terminal();
			(* Node)->SetStripID(m_StripID);
			ClockWise = ! ClockWise;
		}
	}


	if (ClockWise)
		return strip();

	if (Cache()) {
		m_Cache.merge(m_BackCache, Size);
		m_BackCache.reset();
	}

	return strip(Node - m_Triangles.begin(), Order, Size);
}

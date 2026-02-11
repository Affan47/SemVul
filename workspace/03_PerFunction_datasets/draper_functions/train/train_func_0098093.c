insertSite(const Vertex &v)
{
	QuadEdge *e = locate(v);

	if ((v.equals(e->orig(), tolerance)) || (v.equals(e->dest(), tolerance))) {
		return *e;
	}


	QuadEdge *base = &makeEdge(e->orig(), v);
	QuadEdge::splice(*base, *e);
	QuadEdge *startEdge = base;
	do {
		base = &connect(*e, base->sym());
		e = &base->oPrev();
	} while (&e->lNext() != startEdge);

	return *startEdge;
}

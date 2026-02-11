operator<< (std::ostream& o, const BoundaryElement& A)
{
	o << A.tag << ' ' << A.edge << ' ' << A.left << ' ' << A.right;
	if (A.c != NULL)
		o << " 203 " << A.a->tag << ' ' << A.b->tag << ' ' << A.c->tag << '\n';
	else
		o << " 202 " << A.a->tag << ' ' << A.b->tag << '\n';
	return o;
}

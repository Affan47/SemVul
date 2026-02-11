LastEdge(const triangle & Triangle, const triangle_order Order)
{
	switch (Order)
	{
	case ABC:
		return triangle_edge(Triangle.B(), Triangle.C());

	case BCA:
		return triangle_edge(Triangle.C(), Triangle.A());

	case CAB:
		return triangle_edge(Triangle.A(), Triangle.B());

	default:
		assert(false);
		return triangle_edge(0, 0);
	}
}

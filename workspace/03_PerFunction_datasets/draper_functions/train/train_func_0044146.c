CreateHexahedron(double radius)	{
	if (radius==0.0) return CreateEmpty();
	double r=radius/sqrt(3.0);
	return CreateCubicPrism(-r,r,-r,r,-r,r);
}

CreateRhombicosidodecahedron(double radius)	{
	return CreateIcosahedron(radius*sqrt(10.0/(35.0+9.0*sqrt(5.0))))->cantellate(1.5*(sqrt(5.0)-1));
}

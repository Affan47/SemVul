changeCoordinatesReference(const CPose3D	&newBase)
{
	const size_t N = x.size();

	for (size_t i=0;i<N;i++)
		newBase.composePoint(
			x[i],y[i],z[i],
			x[i],y[i],z[i]
		);

	mark_as_modified();
}

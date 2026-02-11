getSetOfPolygons(std::vector<math::TPolygon3D> &vec) const	{
	if (!polygonsUpToDate) updatePolygons();
	size_t N=tempPolygons.size();
	vec.resize(N);
	for (size_t i=0;i<N;i++) vec[i]=tempPolygons[i].poly;
}

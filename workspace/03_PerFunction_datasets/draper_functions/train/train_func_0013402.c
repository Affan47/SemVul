generatePointCloud(CPointsMap *out_map) const {
	ASSERT_(out_map);
	out_map->clear();


	std::for_each(scanSet.begin(),scanSet.end(),CAngularObservationMesh_fnctr(out_map));
}

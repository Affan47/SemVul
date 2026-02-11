mpoly_to_ogr(const Mpoly &mpoly_in) {
	size_t num_rings_in = mpoly_in.rings.size();

	std::vector<std::vector<int> > holes;
	holes.resize(num_rings_in);

	size_t num_geom_out = 0;
	for(size_t outer_idx=0; outer_idx<num_rings_in; outer_idx++) {
		const Ring &ring = mpoly_in.rings[outer_idx];
		if(ring.is_hole) {
			int parent = ring.parent_id;
			holes[parent].push_back(outer_idx);
		} else {
			num_geom_out++;
		}
	}

	bool use_multi = num_geom_out > 1;

	OGRGeometryH geom_out = OGR_G_CreateGeometry(
		use_multi ? wkbMultiPolygon : wkbPolygon);

	for(size_t outer_idx=0; outer_idx<num_rings_in; outer_idx++) {
		const Ring &ring = mpoly_in.rings[outer_idx];
		if(ring.is_hole) continue;

		OGRGeometryH poly_out = use_multi ?
			OGR_G_CreateGeometry(wkbPolygon) : geom_out;
		OGR_G_AddGeometry(poly_out, ring_to_ogr(ring));

		for(size_t hole_idx=0; hole_idx<holes[outer_idx].size(); hole_idx++) {
			const Ring &hole = mpoly_in.rings[holes[outer_idx][hole_idx]];
			if(hole.parent_id != int(outer_idx)) fatal_error("could not sort out holes");
			OGR_G_AddGeometry(poly_out, ring_to_ogr(hole));
		}

		if(size_t(OGR_G_GetGeometryCount(poly_out)) != holes[outer_idx].size()+1) {
			fatal_error("GeometryCount != num_holes+1 (%d vs. %zd)",
				OGR_G_GetGeometryCount(poly_out), holes[outer_idx].size()+1);
		}

		if(use_multi) OGR_G_AddGeometry(geom_out, poly_out);
	}

	if(use_multi && size_t(OGR_G_GetGeometryCount(geom_out)) != num_geom_out) {
		fatal_error("GeometryCount != num_geom_out (%d vs. %zd)",
			OGR_G_GetGeometryCount(geom_out), num_geom_out);
	}

	return geom_out;
}

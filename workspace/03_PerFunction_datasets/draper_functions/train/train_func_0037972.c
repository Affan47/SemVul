IsCoastalOrLakeside()
{
	if ((type != R_LAKE) && (TerrainDefs[type].similar_type == R_OCEAN)) return 1;
	int seacount = 0;
	for (int i=0; i<NDIRS; i++) {
		if (neighbors[i] && TerrainDefs[neighbors[i]->type].similar_type == R_OCEAN) {
		seacount++;
	}
	}
	return seacount;
}

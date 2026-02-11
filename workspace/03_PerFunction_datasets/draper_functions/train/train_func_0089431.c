Inside(const dReal* AABB){
	return AABB[AXIS0 * 2 + 0] >= MinX && AABB[AXIS0 * 2 + 1] <= MaxX && AABB[AXIS1 * 2 + 0] >= MinZ && AABB[AXIS1 * 2 + 1] <= MaxZ;
}

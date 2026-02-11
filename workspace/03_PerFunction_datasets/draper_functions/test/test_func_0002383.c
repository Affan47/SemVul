occludes(const BlockIdx& bi) const
{
	int64_t dx = bi.x - x, dz = bi.z - z, dy = bi.y - y;

	if (dx < 0 || dz > 0 || dy > 0)
		return false;


	int64_t imgxdiff = dx*2 + dz*2;
	int64_t imgydiff = -dx + dz - dy*2;
	return imgxdiff <= 2 && imgydiff <= 2;
}

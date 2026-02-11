GdipPathIterGetSubpathCount (GpPathIterator *iterator, int *count)
{
	int numSubpaths = 0;

	if (!iterator || !count)
		return InvalidParameter;

	if (iterator->path) {
		int i;
		BYTE type;

		for (i = 0; i < iterator->path->count; i++) {
			type = g_array_index (iterator->path->types, BYTE, i);
			if (type == PathPointTypeStart)
				numSubpaths++;
		}
	}

	*count = numSubpaths;

	return Ok;
}

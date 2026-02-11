GdipClosePathFigures (GpPath *path)
{
	int index = 0;
	BYTE currentType;
	BYTE lastType;
	GByteArray *oldTypes;

	if (!path)
		return InvalidParameter;


	if (path->count <= 1)
		return Ok;

	oldTypes = path->types;
	path->types = g_byte_array_new ();

	lastType = g_array_index (oldTypes, BYTE, index);
	index++;

	for (index = 1; index < path->count; index++) {
		currentType = g_array_index (oldTypes, BYTE, index);

		if ((currentType == PathPointTypeStart) && (index > 1)) {
			lastType |= PathPointTypeCloseSubpath;
			g_byte_array_append (path->types, &lastType, 1);
		}
		else
			g_byte_array_append (path->types, &lastType, 1);

		lastType = currentType;
	}


	lastType |= PathPointTypeCloseSubpath;
	g_byte_array_append (path->types, &lastType, 1);

	path->start_new_fig = TRUE;

	g_byte_array_free (oldTypes, TRUE);

        return Ok;
}

GdipReversePath (GpPath *path)
{
	int length, i;
	GArray *points;
	GByteArray *types;
	int start = 0;
	BOOL prev_had_marker = FALSE;

	if (!path)
		return InvalidParameter;

	length = path->count;

	if (length <= 1)
		return Ok;


	types = g_byte_array_sized_new (length);
	if (!types)
		return OutOfMemory;

	for (i = 1; i < length; i++) {
		BYTE t = g_array_index (path->types, BYTE, i);
		if ((t & PathPointTypePathTypeMask) == PathPointTypeStart) {
			reverse_subpath_adjust_flags (start, i - 1, path->types, types, &prev_had_marker);
			start = i;
		}
	}
	if (start < length - 1)
		reverse_subpath_adjust_flags (start, length - 1, path->types, types, &prev_had_marker);


	for (i = 0; i < (length >> 1); i++) {
		BYTE *a = &g_array_index (types, BYTE, i);
		BYTE *b = &g_array_index (types, BYTE, length - i - 1);
		BYTE temp = *a;
		*a = *b;
		*b = temp;
	}
	g_byte_array_free (path->types, TRUE);
	path->types = types;


        for (i = 0; i < (length >> 1); i++) {
		GpPointF *first = &g_array_index (path->points, GpPointF, i);
		GpPointF *last = &g_array_index (path->points, GpPointF, length - i - 1);

		GpPointF temp;
		temp.X = first->X;
		temp.Y = first->Y;
		first->X = last->X;
		first->Y = last->Y;
		last->X = temp.X;
		last->Y = temp.Y;
        }

        return Ok;
}

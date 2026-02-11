GdipGetPathPoints (GpPath *path, GpPointF *points, int count)
{
	int i;

	if (!path || !points || (count < 1))
		return InvalidParameter;

	if (count > path->count)
		count = path->count;

        for (i = 0; i < count; i++) {
		GpPointF point = g_array_index (path->points, GpPointF, i);
                points [i].X = point.X;
                points [i].Y = point.Y;
	}

        return Ok;
}

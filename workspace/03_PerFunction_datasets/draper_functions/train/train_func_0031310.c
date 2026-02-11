GdipGetPathWorldBounds (GpPath *path, GpRectF *bounds, const GpMatrix *matrix, const GpPen *pen)
{
	GpStatus status;
	GpPath *workpath = NULL;

	if (!path || !bounds)
		return InvalidParameter;

	if (path->count < 1) {

		bounds->X = 0.0f;
		bounds->Y = 0.0f;
		bounds->Width = 0.0f;
		bounds->Height = 0.0f;
		return Ok;
	}

	status = GdipClonePath (path, &workpath);
	if (status != Ok) {
		if (workpath)
			GdipDeletePath (workpath);
		return status;
	}


	status = GdipFlattenPath (workpath, (GpMatrix*)matrix, 25.0f);
	if (status == Ok) {
		int i;
		GpPointF points;

		points = g_array_index (workpath->points, GpPointF, 0);
		bounds->X = points.X;
		bounds->Y = points.Y;
		if (workpath->count == 1) {

			bounds->Width = 0.0f;
			bounds->Height = 0.0f;
			GdipDeletePath (workpath);
			return Ok;
		}

		bounds->Width = points.X;
		bounds->Height = points.Y;

		for (i = 1; i < workpath->count; i++) {
			points = g_array_index (workpath->points, GpPointF, i);
			if (points.X < bounds->X)
				bounds->X = points.X;
			if (points.Y < bounds->Y)
				bounds->Y = points.Y;
			if (points.X > bounds->Width)
				bounds->Width = points.X;
			if (points.Y > bounds->Height)
				bounds->Height = points.Y;
		}


		bounds->Width -= bounds->X;
		bounds->Height -= bounds->Y;

		if (pen) {

			float width = (pen->width < 1.0f) ? 1.0f : pen->width;
			float halfw = (width / 2);

			bounds->X -= halfw;
			bounds->Y -= halfw;
			bounds->Width += width;
			bounds->Height += width;
		}
	}
	GdipDeletePath (workpath);
	return status;
}

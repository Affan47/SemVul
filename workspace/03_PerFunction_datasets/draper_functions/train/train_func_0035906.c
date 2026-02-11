append_curve (GpPath *path, const GpPointF *points, GpPointF *tangents, int offset, int length, _CurveType type)
{
	int i;
	PathPointType ptype = ((type == CURVE_CLOSE) || (path->count == 0)) ? PathPointTypeStart : PathPointTypeLine;

	append_point (path, points [offset], ptype, TRUE);
	for (i = offset; i < offset + length; i++) {
		int j = i + 1;

		double x1 = points [i].X + tangents [i].X;
		double y1 = points [i].Y + tangents [i].Y;

		double x2 = points [j].X - tangents [j].X;
		double y2 = points [j].Y - tangents [j].Y;

		double x3 = points [j].X;
		double y3 = points [j].Y;

		append_bezier (path, x1, y1, x2, y2, x3, y3);
        }

        if (type == CURVE_CLOSE) {

		double x1 = points [i].X + tangents [i].X;
		double y1 = points [i].Y + tangents [i].Y;

		double x2 = points [0].X - tangents [0].X;
		double y2 = points [0].Y - tangents [0].Y;

		double x3 = points [0].X;
		double y3 = points [0].Y;

		append_bezier (path, x1, y1, x2, y2, x3, y3);
		GdipClosePathFigure (path);
	}
}

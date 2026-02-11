GdipSetPenLineJoin (GpPen *pen, GpLineJoin lineJoin)
{
	if (!pen)
		return InvalidParameter;

	pen->changed = pen->changed ? TRUE : (pen->line_join != lineJoin);
        pen->line_join = lineJoin;
        return Ok;
}

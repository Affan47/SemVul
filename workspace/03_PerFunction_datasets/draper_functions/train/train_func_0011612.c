GdipSetPenMode (GpPen *pen, GpPenAlignment penMode)
{
	if (!pen)
		return InvalidParameter;

	pen->changed = pen->changed ? TRUE : (penMode != pen->mode);
	pen->mode = penMode;
	return Ok;
}

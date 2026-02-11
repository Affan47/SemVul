GdipSetLineWrapMode (GpLineGradient *brush, GpWrapMode wrapMode)
{
	if (!brush || (wrapMode == WrapModeClamp))
		return InvalidParameter;

	brush->wrapMode = wrapMode;
	brush->base.changed = TRUE;
	return Ok;
}

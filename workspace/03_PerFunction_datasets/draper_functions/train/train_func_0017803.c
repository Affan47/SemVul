GdipCreateSolidFill (ARGB color, GpSolidFill **brush)
{
	if (!brush)
		return InvalidParameter;

	*brush = gdip_solidfill_new ();
	if (!*brush)
		return OutOfMemory;

	(*brush)->color = color;
	return Ok;
}

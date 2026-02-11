GdipGetPenFillType (GpPen *pen, GpPenType *type)
{
	if (!pen || !type)
		return InvalidParameter;

	if (pen->brush != NULL)
		return GdipGetBrushType (pen->brush, (GpBrushType *) type);

	*type = PenTypeSolidColor;

	return Ok;
}

GdipRotateTextureTransform (GpTexture *texture, float angle, GpMatrixOrder order)
{
	GpStatus status;

	if (texture == NULL)
		return InvalidParameter;

	status = GdipRotateMatrix (&texture->matrix, angle, order);
	if (status == Ok)
		texture->base.changed = TRUE;

	return status;
}

GdipScaleWorldTransform (GpGraphics *graphics, float sx, float sy, GpMatrixOrder order)
{
	GpStatus s;

	if (!graphics || (sx == 0.0f) || (sy == 0.0f))
		return InvalidParameter;

        s = GdipScaleMatrix (graphics->copy_of_ctm, sx, sy, order);
        if (s != Ok)
                return s;

	s = GdipScaleMatrix (graphics->clip_matrix, (1.0f / sx), (1.0f / sy), gdip_matrix_reverse_order (order));
	if (s != Ok)
		return s;

	apply_world_to_bounds (graphics);

	switch (graphics->backend) {
	case GraphicsBackEndCairo:

		return cairo_SetWorldTransform (graphics, graphics->copy_of_ctm);
	case GraphicsBackEndMetafile:
		return metafile_ScaleWorldTransform (graphics, sx, sy, order);
	default:
		return GenericError;
	}
}

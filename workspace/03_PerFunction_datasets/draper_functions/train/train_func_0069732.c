GdipFillPath (GpGraphics *graphics, GpBrush *brush, GpPath *path)
{
	if (!graphics || !brush || !path)
		return InvalidParameter;

	switch (graphics->backend) {
	case GraphicsBackEndCairo:
		return cairo_FillPath (graphics, brush, path);
	case GraphicsBackEndMetafile:
		return metafile_FillPath (graphics, brush, path);
	default:
		return GenericError;
	}
}

GdipReleaseDC (GpGraphics *graphics, HDC hDC)
{
	if (hDC != (void *)graphics) {
		return InvalidParameter;
	}
	return Ok;
}

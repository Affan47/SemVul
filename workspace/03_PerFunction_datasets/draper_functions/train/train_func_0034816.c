gdip_custom_linecap_destroy (GpCustomLineCap *cap)
{
	if (!cap)
		return InvalidParameter;

	if (cap->fill_path) {
		GdipDeletePath (cap->fill_path);
		cap->fill_path = NULL;
	}
	if (cap->stroke_path) {
		GdipDeletePath (cap->stroke_path);
		cap->stroke_path = NULL;
	}
	GdipFree (cap);

	return Ok;
}

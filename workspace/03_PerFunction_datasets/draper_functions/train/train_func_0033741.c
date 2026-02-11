GdipRecordMetafileFileName (GDIPCONST WCHAR *fileName, HDC referenceHdc, EmfType type, GDIPCONST GpRectF *frameRect,
	MetafileFrameUnit frameUnit, GDIPCONST WCHAR *description, GpMetafile **metafile)
{
	GpStatus status;
	GpMetafile *mf = NULL;
	char *file_name;

	if (!fileName)
		return InvalidParameter;

	file_name = (char *) ucs2_to_utf8 ((const gunichar2 *)fileName, -1);
	if (!file_name) {
		*metafile = NULL;
		return InvalidParameter;
	}

	status = GdipRecordMetafile (referenceHdc, type, frameRect, frameUnit, description, &mf);
	if (status != Ok) {
		GdipFree (file_name);
		return status;
	}


	mf->fp = fopen (file_name, "wb");

	GdipFree (file_name);
	*metafile = mf;
	return Ok;
}

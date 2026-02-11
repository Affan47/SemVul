GdipRecordMetafile (HDC referenceHdc, EmfType type, GDIPCONST GpRectF *frameRect, MetafileFrameUnit frameUnit,
	GDIPCONST WCHAR *description, GpMetafile **metafile)
{
	GpMetafile *mf;

	if (!referenceHdc || !frameRect || !metafile)
		return InvalidParameter;

	if ((type < EmfTypeEmfOnly) || (type > EmfTypeEmfPlusDual))
		return InvalidParameter;

	if ((frameUnit < MetafileFrameUnitPixel) || (frameUnit > MetafileFrameUnitGdi))
		return InvalidParameter;

	if (((frameRect->Width == 0) || (frameRect->Height == 0)) && (frameUnit != MetafileFrameUnitGdi))
		return GenericError;

	mf = gdip_metafile_create ();
	if (!mf)
		return OutOfMemory;

	mf->metafile_header.X = frameRect->X;
	mf->metafile_header.Y = frameRect->Y;
	mf->metafile_header.Width = frameRect->Width;
	mf->metafile_header.Height = frameRect->Height;
	mf->metafile_header.Size = 0;
	mf->metafile_header.Type = type;
	mf->recording = TRUE;


	*metafile = mf;
	return Ok;
}

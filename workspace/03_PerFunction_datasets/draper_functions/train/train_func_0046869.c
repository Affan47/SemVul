gdi_bitmap_new(GDI *gdi, int width, int height, int bpp, uint8* data)
{
	GDI_IMAGE *gdi_bmp;

	gdi_bmp = (GDI_IMAGE*) malloc(sizeof(GDI_IMAGE));
	gdi_bmp->hdc = gdi_CreateCompatibleDC(gdi->hdc);

	DEBUG_GDI("gdi_bitmap_new: width:%d height:%d bpp:%d", width, height, bpp);

	if (data == NULL)
	{
		gdi_bmp->bitmap = gdi_CreateCompatibleBitmap(gdi->hdc, width, height);
	}
	else
	{
		gdi_bmp->bitmap = gdi_create_bitmap(gdi, width, height, bpp, data);
	}

	gdi_SelectObject(gdi_bmp->hdc, (HGDIOBJECT) gdi_bmp->bitmap);
	gdi_bmp->org_bitmap = NULL;

	return gdi_bmp;
}

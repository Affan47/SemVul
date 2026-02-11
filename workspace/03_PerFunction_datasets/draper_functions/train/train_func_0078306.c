BitBlt_PATCOPY_32bpp(HGDI_DC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight)
{
	int x, y;
	uint8 *dstp;
	uint8 *patp;
	uint32 color32;
	uint32 *dstp32;

	if(hdcDest->brush->style == GDI_BS_SOLID)
	{
		color32 = gdi_get_color_32bpp(hdcDest, hdcDest->brush->color);

		for (y = 0; y < nHeight; y++)
		{
			dstp32 = (uint32*) gdi_get_bitmap_pointer(hdcDest, nXDest, nYDest + y);

			if (dstp32 != 0)
			{
				for (x = 0; x < nWidth; x++)
				{
					*dstp32 = color32;
					dstp32++;
				}
			}
		}
	}
	else
	{
		for (y = 0; y < nHeight; y++)
		{
			dstp = gdi_get_bitmap_pointer(hdcDest, nXDest, nYDest + y);

			if (dstp != 0)
			{
				for (x = 0; x < nWidth; x++)
				{
					patp = gdi_get_brush_pointer(hdcDest, x, y);

					*dstp = *patp;
					patp++;
					dstp++;

					*dstp = *patp;
					patp++;
					dstp++;

					*dstp = *patp;
					dstp += 2;
				}
			}
		}
	}

	return 0;
}

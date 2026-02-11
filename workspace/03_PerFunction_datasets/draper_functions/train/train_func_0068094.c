gdip_region_bitmap_get_scans (GpRegionBitmap *bitmap, GpRectF *rect, int count)
{
	GpRect actual;
	int x, y, w;
	int n = 0;

	actual.X = REGION_INFINITE_POSITION;
	actual.Width = REGION_INFINITE_LENGTH;

	for (y = bitmap->Y; y < bitmap->Y + bitmap->Height; y++) {

		x = bitmap->X;
		while (process_line (bitmap, y, &x, &w)) {


			if ((x == actual.X) && (w == actual.Width)) {

				if (rect && (n > 0)) {
					rect [n - 1].Height++;
				}
			} else {
				actual.X = x;
				actual.Y = y;
				actual.Width = w;
				actual.Height = 1;

				if (rect && (n < count)) {
					rect [n].X = actual.X;
					rect [n].Y = actual.Y;
					rect [n].Width = actual.Width;
					rect [n].Height = actual.Height;
				}
				n++;
			}

			x += w + 1;
		}
	}
	return n;
}

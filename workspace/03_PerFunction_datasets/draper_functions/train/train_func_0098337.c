GdipAddPathRectanglesI (GpPath *path, const GpRect *rects, int count)
{
        int i;

	if (!path || !rects)
		return InvalidParameter;

        for (i = 0; i < count; i++) {
                float x = (float) rects[i].X;
                float y = (float) rects[i].Y;
                float width =  (float) rects[i].Width;
                float height =  (float) rects[i].Height;
                GdipAddPathRectangle (path, x, y, width, height);
        }

        return Ok;
}

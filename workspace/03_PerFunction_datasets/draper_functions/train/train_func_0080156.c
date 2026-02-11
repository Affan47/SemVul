g_array_to_array (GArray *p)
{
        int length = p->len;
        GpPointF *pts = (GpPointF *) GdipAlloc (sizeof (GpPointF) * length);
	if (!pts)
		return NULL;

        memcpy (pts, p->data, p->len * sizeof (GpPointF));

        return pts;
}

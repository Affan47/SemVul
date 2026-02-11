skin_load_pixbuf (GdkPixbuf * tmp_pixbuf, int deep,int x[],int y[],int w, int h, GdkPixbuf* p[])
{
	for (int i=0; i< deep; i++)
	{
		p[i]=gdk_pixbuf_new_subpixbuf(tmp_pixbuf, x[i+1], y[i+1], w, h);
	}
}

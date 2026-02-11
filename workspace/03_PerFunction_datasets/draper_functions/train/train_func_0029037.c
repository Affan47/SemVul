resize(int w, int h)
{
	if (pr && pr->getClass() == Type_gSplitter)
		return;

	if (w < 1)
		w = 0;

	if (h < minimumHeight())
		h = minimumHeight();

	if (bufW == w && bufH == h)
		return;

	if (w < 1 || h < 1)
	{
		bufW = w;
		bufH = h;

		if (visible)
			gtk_widget_hide(border);
	}
	else
	{
		bufW = w;
		bufH = h;

		if (frame && widget != border)
		{
			int fw = getFrameWidth() * 2;
			if (w < fw || h < fw)
				gtk_widget_hide(widget);
			else
				gtk_widget_show(widget);
		}

		if (visible)
			gtk_widget_show(border);


		_dirty_size = true;

		#if GEOMETRY_OPTIMIZATION
		gApplication::setDirty();
		#else
		updateGeometry();
		#endif
	}

	if (pr)
		pr->performArrange();

	send_configure(this);
}

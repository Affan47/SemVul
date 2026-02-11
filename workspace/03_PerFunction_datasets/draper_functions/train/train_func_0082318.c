glog(const char *fmt, ...)
{
	xtra_win_data *xd = &xdata[4];

	char str[80];
	va_list vp;

	if (GTK_IS_TEXT_VIEW(xd->text_view))
	{
		xd->buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(xd->text_view));
		if (!GTK_IS_TEXT_BUFFER(xd->buf))
		{
			xd->buf = gtk_text_buffer_new(NULL);
			gtk_text_view_set_buffer(GTK_TEXT_VIEW (xd->text_view), xd->buf);
		}
		init_color_tags(xd);
	}

	va_start(vp, fmt);
	(void)vstrnfmt(str, sizeof(str), fmt, vp);
	va_end(vp);

	#ifdef VERBOSE_DEBUG
	if (GTK_IS_TEXT_VIEW(xd->text_view))
		plog(str);
	#endif

	if (GTK_IS_TEXT_VIEW(xd->text_view))
		text_view_print(xd, str, TERM_WHITE);
	else
		plog(str);
}

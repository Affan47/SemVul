notify_eraser_of_bg_color_change(void)
{
	GdkCursor *cursor;

    if ( m_priv == NULL ) return;

	cursor = create_eraser_cursor(m_priv->eraser_type);

	if(!cursor)
	{
		cursor = gdk_cursor_new ( GDK_CROSSHAIR );
		g_assert(cursor);
	}
	gdk_window_set_cursor ( m_priv->cv->drawing, cursor );
	gdk_cursor_unref( cursor );
}

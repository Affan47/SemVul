reset ( void )
{
	GdkCursor *cursor = gdk_cursor_new ( GDK_DOTBOX );
	g_assert(cursor);
	gdk_window_set_cursor ( m_priv->cv->drawing, cursor );
	gdk_cursor_unref( cursor );
	m_priv->is_draw = FALSE;
}

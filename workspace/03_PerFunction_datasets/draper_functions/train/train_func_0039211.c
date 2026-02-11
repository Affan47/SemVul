tool_rect_select_init ( gp_canvas * canvas )
{
    GdkPoint s = {0, 0};
    GdkPoint e = {0, 0};

    gp_selection_init ();
	create_private_data ();
	m_priv->cv					= canvas;
	m_priv->tool.button_press	= button_press;
	m_priv->tool.button_release	= button_release;
	m_priv->tool.button_motion	= button_motion;
	m_priv->tool.draw			= draw;
	m_priv->tool.reset			= reset;
	m_priv->tool.destroy		= destroy;


	if(GDK_IS_PIXBUF(canvas->pb_clipboard))
	{
		e.x = gdk_pixbuf_get_width(canvas->pb_clipboard);
		e.x += s.x;
		e.y = gdk_pixbuf_get_height(canvas->pb_clipboard);
		e.y += s.y;
		if(gp_selection_create (&s, &e, canvas->pb_clipboard)){
			m_priv->state   =   SEL_WAITING;
		}
		g_object_unref(canvas->pb_clipboard);
		canvas->pb_clipboard = NULL;
	}

	return &m_priv->tool;
}

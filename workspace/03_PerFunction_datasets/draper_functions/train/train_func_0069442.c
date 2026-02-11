button_motion ( GdkEventMotion *event )
{
	GdkModifierType state;
	gint x, y;

	if( m_priv->is_draw )
	{
        if (event->is_hint)
		{
			gdk_window_get_pointer (event->window, &x, &y, &state);
		}
		else
		{
			x = event->x;
			y = event->y;
			state = event->state;
		}

		m_priv->pt.x = x;
		m_priv->pt.y = y;


		m_priv->pt.x -= m_priv->rad;
		m_priv->pt.y -= m_priv->rad;

        gtk_widget_queue_draw ( m_priv->cv->widget );
	}
	return TRUE;
}

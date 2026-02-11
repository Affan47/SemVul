on_button_press_event(GdkEventButton* event)
{
	if( event->type == GDK_BUTTON_PRESS  )
	{
		m_mouseDown = true;
		m_mouseDelta = event->y;

		return true;
	}
	else
	{
		return false;
	}
}

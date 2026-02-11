on_mouse_up(GtkWidget* widget UNUSED, GdkEventButton* evt, CTermView* _this)
{
	switch(evt->button)
	{
	case 1:
		_this->OnLButtonUp(evt);
		break;
	case 3:
		_this->OnRButtonUp(evt);
	}
	return true;
}

tray_up (GtkWidget *widget,GdkEventButton *event,gTrayIcon *data)
{
	if (!gApplication::userEvents()) return false;
	if (gApplication::loopLevel() > data->loopLevel()) return false;

	if (data->onMouseRelease)
	{
		gMouse::validate();
		gMouse::setMouse((int)event->x, (int)event->y, event->button, event->state);
		data->onMouseRelease(data);
		gMouse::invalidate();
	}

	return false;
}

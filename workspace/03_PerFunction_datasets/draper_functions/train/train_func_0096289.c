OnMotion (Canvas *canvas, GdkEventMotion *event)
{
	Item *item = NULL;
	canvas->m_LastEventState = event->state;
	double x = event->x / canvas->m_Zoom, y = event->y / canvas->m_Zoom;
	if (canvas->m_Root->Distance (x, y, &item) > canvas->m_Gap)
		item = NULL;
	ItemClient *client = (item)? item->GetClient (): NULL;
	return (canvas->m_Client)? (canvas->m_Dragging? canvas->m_Client->OnDrag (client, x, y, event->state): canvas->m_Client->OnMotion (client, x, y, event->state)): true;
}

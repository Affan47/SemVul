unselect_port(GanvPort* p)
{
	_selected_ports.erase(p);
	g_object_set(G_OBJECT(p), "selected", FALSE, NULL);
	if (_last_selected_port == p) {
		_last_selected_port = NULL;
	}
}

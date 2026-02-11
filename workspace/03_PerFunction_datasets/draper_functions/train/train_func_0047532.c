select_port(GanvPort* p, bool unique)
{
	if (unique) {
		unselect_ports();
	}
	g_object_set(G_OBJECT(p), "selected", TRUE, NULL);
	_selected_ports.insert(p);
	_last_selected_port = p;
}

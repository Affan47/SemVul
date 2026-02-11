ganv_port_set_direction(GanvPort*     port,
                        GanvDirection direction)
{
	GanvNode* node     = GANV_NODE(port);
	GanvBox*  box      = GANV_BOX(port);
	gboolean  is_input = port->impl->is_input;
	switch (direction) {
	case GANV_DIRECTION_RIGHT:
		box->impl->radius_tl = (is_input ? 0.0 : 4.0);
		box->impl->radius_tr = (is_input ? 4.0 : 0.0);
		box->impl->radius_br = (is_input ? 4.0 : 0.0);
		box->impl->radius_bl = (is_input ? 0.0 : 4.0);
		break;
	case GANV_DIRECTION_DOWN:
		box->impl->radius_tl = (is_input ? 0.0 : 4.0);
		box->impl->radius_tr = (is_input ? 0.0 : 4.0);
		box->impl->radius_br = (is_input ? 4.0 : 0.0);
		box->impl->radius_bl = (is_input ? 4.0 : 0.0);
		break;
	}
	ganv_node_set_show_label(node, direction == GANV_DIRECTION_RIGHT);
	ganv_node_resize(node);
}

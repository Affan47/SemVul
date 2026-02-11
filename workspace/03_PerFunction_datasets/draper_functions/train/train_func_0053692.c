mouse_save(CtrlInfo *ctrl, FILE *out)
{
	GSList	*mouse, *iter;

	xml_put_node_open(out, "MouseButtons");
	if((mouse = ctrl_mouse_get_list(ctrl)) != NULL)
	{
		for(iter = mouse; iter != NULL; iter = g_slist_next(iter))
		{
			xml_put_node_open(out, "MouseButton");
			xml_put_uinteger(out, "button", ctrl_mouse_get_button(iter->data));
			xml_put_uinteger(out, "state", ctrl_mouse_get_state(iter->data));
			xml_put_text(out, "cmdseq", ctrl_mouse_get_cmdseq(iter->data));
			xml_put_node_close(out, "MouseButton");
		}
		g_slist_free(mouse);
	}
	xml_put_node_close(out, "MouseButtons");
}

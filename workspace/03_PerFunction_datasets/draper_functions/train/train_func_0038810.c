sig_layout_window_save(WINDOW_REC *window, CONFIG_NODE *node)
{
	WINDOW_REC *active;
        GUI_WINDOW_REC *gui;

        gui = WINDOW_GUI(window);
	if (gui->sticky) {
		iconfig_node_set_bool(node, "sticky", TRUE);
		active = gui->parent->active;
		if (window != active)
			iconfig_node_set_int(node, "parent", active->refnum);
	}

	if (gui->use_scroll)
                iconfig_node_set_bool(node, "scroll", gui->scroll);
}

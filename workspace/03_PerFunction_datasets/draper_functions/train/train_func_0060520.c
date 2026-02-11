show_section (CmdConfig *cmd_config, CameraWidget *section)
{
	CameraWidget *child, *parent;
	CameraWidgetType type;
	CDKSCROLL *scroll = NULL;
	const char *label;
	char *items[100];
	int count, x, selection;
	char title[1024];
	int show_parent = 0, show_child = 0;


	gp_widget_get_type (section, &type);
	gp_widget_get_label (section, &label);
	snprintf (title, sizeof (title), "<C></5>%s", label);
	if (type == GP_WIDGET_WINDOW)
		items[0] = copyChar (_("Exit"));
	else
		items[0] = copyChar (_("Back"));
	count = gp_widget_count_children (section);
	for (x = 0; x < count; x++) {
		gp_widget_get_child (section, x, &child);
		gp_widget_get_label (child, &label);
		items[x + 1] = copyChar ((char *) label);
	}
	count++;
	scroll = newCDKScroll (cmd_config->screen, CENTER, CENTER, RIGHT,
			       10, 50, title,
			       items, count, NUMBERS, A_REVERSE, TRUE, FALSE);
	if (!scroll)
		return (GP_ERROR);

	selection = activateCDKScroll (scroll, 0);
	if (scroll->exitType == vNORMAL) {
		if (selection)
			show_child = selection;
		else if (type != GP_WIDGET_WINDOW)
			show_parent = 1;
	}


	destroyCDKScroll (scroll);

	if (show_parent) {
		gp_widget_get_parent (section, &parent);
		show_widget (cmd_config, parent);
	} else if (show_child) {
		gp_widget_get_child (section, show_child - 1, &child);
		show_widget (cmd_config, child);
	}

	return (GP_OK);
}

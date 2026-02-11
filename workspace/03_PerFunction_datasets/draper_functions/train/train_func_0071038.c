serialize (struct RcBlock const	*block,
	   GString		*rc_string)
{
	GString		*colors;
	GSList const	*iter;
	char		*style;
	char		*style_name;
	char const      *rc_selector;

	if (strlen (block->type_name) > 3 &&
	    0 == strncmp ("Gtk", block->type_name, 3)) {
		style = g_ascii_strdown (block->type_name + 3, -1);
	} else if (0 == strcmp ("*", block->type_name)) {
		style = g_strdup ("default");
	} else {
		return false;
	}

	style_name = g_strdup_printf ("gce-%s", style);
	g_free (style), style = NULL;

	g_string_append_printf (rc_string, "style \"%s\" {\n", style_name);


	colors = g_string_new (NULL);
	if (NORMAL_SET & block->flags) {
		serialize_state (&block->colors[NORMAL], "NORMAL", colors);
	}

	if (ACTIVE_SET & block->flags) {
		serialize_state (&block->colors[ACTIVE], "ACTIVE", colors);
	}

	if (PRELIGHT_SET & block->flags) {
		serialize_state (&block->colors[PRELIGHT], "PRELIGHT", colors);
	}

	if (SELECTED_SET & block->flags) {
		serialize_state (&block->colors[SELECTED], "SELECTED", colors);
	}

	if (INSENSITIVE_SET & block->flags) {
		serialize_state (&block->colors[INSENSITIVE], "INSENSITIVE", colors);
	}

	g_string_append (rc_string, colors->str);


	iter = block->style_properties;
	while (iter) {
		g_string_append_printf (rc_string, "\t%s\n", (char const *) iter->data);
		iter = iter->next;
	}


	g_string_append (rc_string, "\tengine \"css\" {\n");
	g_string_append_printf (rc_string, "\t\tselector = \"%s\"\n", block->type_name);
	g_string_append (rc_string, "\t}\n");


	g_string_append (rc_string, "}\n");

	g_string_append_printf (rc_string, "class \"%s\" style \"%s\"\n\n", block->type_name, style_name);


	rc_selector = get_rc_selector (block->type_name);
	if (rc_selector) {
		g_string_append_printf (rc_string, "%s style \"%s\"\n\n", rc_selector, style_name);
	}

	g_string_free (colors, true);
	g_free (style_name), style_name = NULL;

	return true;
}

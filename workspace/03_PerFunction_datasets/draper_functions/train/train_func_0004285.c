homebank_save_xml_cat(GIOChannel *io)
{
GList *list;
GString *node;
char buf[G_ASCII_DTOSTR_BUF_SIZE];
guint i;

	node = g_string_sized_new(255);

	list = category_glist_sorted(0);
	while (list != NULL)
	{
	Category *item = list->data;

		if(item->key != 0)
		{
			g_string_assign(node, "<cat ");

			hb_xml_append_int(node, "key", item->key);
			hb_xml_append_int(node, "parent", item->parent);
			hb_xml_append_int(node, "flags", item->flags);
			hb_xml_append_txt(node, "name", item->name);

			for(i=0;i<=12;i++)
			{
				if(item->budget[i] != 0)
				{
					g_string_append_printf(node,"b%d=\"%s\" ", i, g_ascii_dtostr (buf, sizeof (buf), item->budget[i]));
				}
			}

			g_string_append(node, "/>\n");
			g_io_channel_write_chars(io, node->str, -1, NULL, NULL);

		}
		list = g_list_next(list);
	}
	g_list_free(list);
	g_string_free(node, TRUE);
}

cdp_save(MainInfo *min, FILE *out)
{
	guint	i, num = sizeof min->cfg.dp_format / sizeof min->cfg.dp_format[0];

	xml_put_node_open(out, NODE);
	xml_put_integer(out, "count", num);
	for(i = 0; i < num; i++)
		save_pane(out, &min->cfg.dp_format[i], config_name[i]);
	save_paning(out, &min->cfg.dp_paning);
	save_history(out, &min->cfg.dp_history);
	xml_put_node_close(out, NODE);

	return TRUE;
}

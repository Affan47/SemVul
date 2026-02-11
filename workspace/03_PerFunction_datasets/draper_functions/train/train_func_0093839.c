cpt_save(MainInfo *min, FILE *out)
{
	gint	i;

	xml_put_node_open(out, NODE);

	xml_put_node_open(out, "PathList");
	for(i = 0; i < PTID_NUM_PATHS; i++)
	{
		xml_put_node_open(out, "Path");
		xml_put_integer(out, "index", i);
		xml_put_text(out, "path", min->cfg.path.path[i]->str);
		xml_put_node_close(out, "Path");
	}
	xml_put_node_close(out, "PathList");

	xml_put_node_open(out, "HideInfo");
	xml_put_integer(out, "mode", min->cfg.path.hideinfo.mode);
 	xml_put_text(out, "re", min->cfg.path.hideinfo.hide_re_src);
	xml_put_boolean(out, "re_nocase", min->cfg.path.hideinfo.no_case);
	xml_put_node_close(out, "HideInfo");

	xml_put_node_close(out, NODE);

	return TRUE;
}

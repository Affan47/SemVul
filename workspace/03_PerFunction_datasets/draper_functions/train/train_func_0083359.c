copy_config(struct pref_struct *tgt, const struct pref_struct *src)
{
  if (tgt == src)
	return;


  free_config(tgt);


  tgt->name_res=src->name_res;
  tgt->diagram_only = src->diagram_only;
  tgt->group_unk = src->group_unk;
  tgt->stationary = src->stationary;
  tgt->node_radius_multiplier = src->node_radius_multiplier;
  tgt->link_node_ratio = src->link_node_ratio;
  tgt->size_mode = src->size_mode;
  tgt->node_size_variable = src->node_size_variable;
  tgt->filter=g_strdup(src->filter);
  tgt->text_color=g_strdup(src->text_color);
  tgt->fontname=g_strdup(src->fontname);
  tgt->center_node=g_strdup(src->center_node);
  tgt->stack_level = src->stack_level;
  tgt->colors = g_strdupv(src->colors);

  tgt->proto_timeout_time = src->proto_timeout_time;
  tgt->gui_node_timeout_time = src->gui_node_timeout_time;
  tgt->node_timeout_time = src->node_timeout_time;
  tgt->proto_node_timeout_time = src->proto_node_timeout_time;
  tgt->gui_link_timeout_time = src->gui_link_timeout_time;
  tgt->link_timeout_time = src->link_timeout_time;
  tgt->proto_link_timeout_time = src->proto_link_timeout_time;

  tgt->refresh_period = src->refresh_period;
  tgt->averaging_time = src->averaging_time;
}

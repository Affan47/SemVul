remap_types_init_combos(struct remap_types *rt)
{
	sediffx_policy_e i;
	for (i = SEDIFFX_POLICY_ORIG; i < SEDIFFX_POLICY_NUM; i++) {
		gtk_combo_box_set_model(GTK_COMBO_BOX(rt->combo[i]), GTK_TREE_MODEL(types_filter[i]));
		gtk_combo_box_entry_set_text_column(rt->combo[i], 0);
		g_signal_connect(rt->combo[i], "changed", G_CALLBACK(remap_types_on_combo_change), rt);
	}
}

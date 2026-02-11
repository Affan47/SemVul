get_recipe_flags(GtkWidget *dialog)
{
	int flags = 0;
	if (get_named_checkb_val(GTK_WIDGET(dialog), "std_checkb"))
		flags |= MKRCP_STD;
	if (get_named_checkb_val(GTK_WIDGET(dialog), "catalog_checkb"))
		flags |= MKRCP_CAT;
	if (get_named_checkb_val(GTK_WIDGET(dialog), "var_checkb"))
		flags |= MKRCP_TGT;
	if (get_named_checkb_val(GTK_WIDGET(dialog), "field_checkb"))
		flags |= MKRCP_FIELD;
	if (get_named_checkb_val(GTK_WIDGET(dialog), "user_checkb"))
		flags |= MKRCP_USER;
	if (get_named_checkb_val(GTK_WIDGET(dialog), "det_checkb"))
		flags |= MKRCP_DET;
	if (get_named_checkb_val(GTK_WIDGET(dialog), "convfield_checkb"))
		flags |= MKRCP_FIELD_TO_TGT;
	if (get_named_checkb_val(GTK_WIDGET(dialog), "convcat_checkb"))
		flags |= MKRCP_CAT_TO_STD;
	if (get_named_checkb_val(GTK_WIDGET(dialog), "convuser_checkb"))
		flags |= MKRCP_USER_TO_TGT;
	if (get_named_checkb_val(GTK_WIDGET(dialog), "convdet_checkb"))
		flags |= MKRCP_DET_TO_TGT;
	if (get_named_checkb_val(GTK_WIDGET(dialog), "off_frame_checkb"))
		flags |= MKRCP_INCLUDE_OFF_FRAME;
	return flags;
}

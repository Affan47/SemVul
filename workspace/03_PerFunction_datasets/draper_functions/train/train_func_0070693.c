gnm_dao_init (GnmDao *gdao)
{
	GtkWidget *toplevel;

	gdao->gui = gnm_gtk_builder_load ("dao.ui", NULL, NULL);
	if (gdao->gui == NULL)
		return;

	toplevel = go_gtk_builder_get_widget (gdao->gui, "output-grid");

	gdao->new_sheet  = go_gtk_builder_get_widget (gdao->gui,
						 "newsheet-button");
	gdao->new_workbook  = go_gtk_builder_get_widget (gdao->gui,
						    "newworkbook-button");
	gdao->output_range  = go_gtk_builder_get_widget (gdao->gui,
						    "outputrange-button");
	gdao->in_place  = go_gtk_builder_get_widget (gdao->gui,
						    "inplace-button");
	gdao->clear_outputrange_button = go_gtk_builder_get_widget
		(gdao->gui, "clear_outputrange_button");
	gdao->retain_format_button = go_gtk_builder_get_widget
		(gdao->gui, "retain_format_button");
	gdao->retain_comments_button = go_gtk_builder_get_widget
		(gdao->gui, "retain_comments_button");
	gdao->put_menu = go_gtk_builder_get_widget
		(gdao->gui, "put_menu");
	gtk_combo_box_set_active
		(GTK_COMBO_BOX (gdao->put_menu), 1);
	gdao->output_entry = NULL;
	gdao->wbcg = NULL;

	gtk_container_add (GTK_CONTAINER (gdao), toplevel);
}

do_current_file_menu(GtkWidget ** parent_menu, gboolean editor_menu)
{
	GtkWidget *cur_file_menu = NULL;

	cur_file_menu = gtk_menu_new();

	if (editor_menu == TRUE)
		*parent_menu = gtk_image_menu_item_new_with_mnemonic(_("_VC file Actions"));
	else
		*parent_menu = gtk_image_menu_item_new_with_mnemonic(_("_File"));
	g_signal_connect(* parent_menu, "activate", G_CALLBACK(update_menu_items), NULL);


	menu_vc_diff_file = gtk_menu_item_new_with_mnemonic(_("_Diff"));
	gtk_container_add(GTK_CONTAINER(cur_file_menu), menu_vc_diff_file);
	ui_widget_set_tooltip_text(menu_vc_diff_file,
			     _("Make a diff from the current active file"));

	g_signal_connect(menu_vc_diff_file, "activate", G_CALLBACK(vcdiff_file_activated), NULL);


	menu_vc_revert_file = gtk_menu_item_new_with_mnemonic(_("_Revert"));
	gtk_container_add(GTK_CONTAINER(cur_file_menu), menu_vc_revert_file);
	ui_widget_set_tooltip_text(menu_vc_revert_file,
			     _("Restore pristine working copy file (undo local edits)."));

	g_signal_connect(menu_vc_revert_file, "activate", G_CALLBACK(vcrevert_activated), NULL);


	gtk_container_add(GTK_CONTAINER(cur_file_menu), gtk_separator_menu_item_new());


	menu_vc_blame = gtk_menu_item_new_with_mnemonic(_("_Blame"));
	gtk_container_add(GTK_CONTAINER(cur_file_menu), menu_vc_blame);
	ui_widget_set_tooltip_text(menu_vc_blame,
			     _("Shows the changes made at one file per revision and author."));

	g_signal_connect(menu_vc_blame, "activate", G_CALLBACK(vcblame_activated), NULL);

	gtk_container_add(GTK_CONTAINER(cur_file_menu), gtk_separator_menu_item_new());


	menu_vc_log_file = gtk_menu_item_new_with_mnemonic(_("_History (log)"));
	gtk_container_add(GTK_CONTAINER(cur_file_menu), menu_vc_log_file);
	ui_widget_set_tooltip_text(menu_vc_log_file,
			     _("Shows the log of the current file"));

	g_signal_connect(menu_vc_log_file, "activate", G_CALLBACK(vclog_file_activated), NULL);


	menu_vc_show_file = gtk_menu_item_new_with_mnemonic(_("_Original"));
	gtk_container_add(GTK_CONTAINER(cur_file_menu), menu_vc_show_file);
	ui_widget_set_tooltip_text(menu_vc_show_file,
			     _("Shows the original of the current file"));

	g_signal_connect(menu_vc_show_file, "activate", G_CALLBACK(vcshow_file_activated), NULL);


	gtk_container_add(GTK_CONTAINER(cur_file_menu), gtk_separator_menu_item_new());


	menu_vc_add_file = gtk_menu_item_new_with_mnemonic(_("_Add to Version Control"));
	gtk_container_add(GTK_CONTAINER(cur_file_menu), menu_vc_add_file);
	ui_widget_set_tooltip_text(menu_vc_add_file, _("Add file to repository."));

	g_signal_connect(menu_vc_add_file, "activate",
			 G_CALLBACK(vcadd_activated), NULL);


	menu_vc_remove_file = gtk_menu_item_new_with_mnemonic(_("_Remove from Version Control"));
	gtk_container_add(GTK_CONTAINER(cur_file_menu), menu_vc_remove_file);
	ui_widget_set_tooltip_text(menu_vc_remove_file, _("Remove file from repository."));

	g_signal_connect(menu_vc_remove_file, "activate", G_CALLBACK(vcremove_activated), NULL);


	gtk_menu_item_set_submenu(GTK_MENU_ITEM(*parent_menu), cur_file_menu);
}

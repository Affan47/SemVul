fpm_save_passitem(GtkWidget* win_edit, fpm_data* data)
{
  gint row = -1;
  gchar* orig_plaintext;
  gchar plaintext[FPM_PASSWORD_LEN+1] = {0};
  GtkEntry* entry;
  GtkTextView* notes;
  gchar *dia_str;

  fpm_data* data1;

  GtkTextIter start, end;
  GtkTextBuffer *buffer;
  GtkTreeIter iter;
  GtkTreeModel *model;
  gboolean valid;


  fpm_dirty(TRUE);


  data->title = fpm_get_entry(win_edit, "entry_title");
  data->arg = fpm_get_entry(win_edit, "entry_arg");
  data->user = fpm_get_entry(win_edit, "entry_user");
  data->category = fpm_get_combo_entry(win_edit, "combo_box_category");
  data->launcher = fpm_get_combo_entry(win_edit, "combo_box_launcher");


  data->default_list = (GTK_TOGGLE_BUTTON(lookup_widget(win_edit, "checkbutton_default"))->active);


  entry = GTK_ENTRY(lookup_widget(win_edit, "entry_password"));

  orig_plaintext = gtk_editable_get_chars (GTK_EDITABLE(entry), 0, -1);

  if ( strlen(orig_plaintext) > (FPM_PASSWORD_LEN -1 )) {
	dia_str = g_malloc0(256);
	sprintf(dia_str, _("Password exceeded limit of %d characters"
		"\nYour password of %d characters was truncated."),
		FPM_PASSWORD_LEN-1, (int) strlen(orig_plaintext));

	fpm_message(GTK_WINDOW(win_edit), dia_str, GTK_MESSAGE_INFO);
	g_free(dia_str);
  }

  wipememory(plaintext, FPM_PASSWORD_LEN);
  strncpy(plaintext, orig_plaintext, FPM_PASSWORD_LEN-1);

  fpm_encrypt_field(old_context, data->password, plaintext, FPM_PASSWORD_LEN);
  wipememory(orig_plaintext, strlen(orig_plaintext));
  wipememory(plaintext, FPM_PASSWORD_LEN);

  g_free(orig_plaintext);


  notes = GTK_TEXT_VIEW(lookup_widget(win_edit, "text_notes"));
  gtk_text_view_set_editable (GTK_TEXT_VIEW (notes), TRUE);
  g_free(data->notes);
  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (notes));
  gtk_text_buffer_get_bounds (buffer, &start, &end);
  data->notes = gtk_text_iter_get_text (&start, &end);

  model = gtk_tree_view_get_model(gui->main_clist);
  valid = gtk_tree_model_get_iter_first(model, &iter);

  while (valid) {
    gtk_tree_model_get(model, &iter, FPM_DATA_POINTER, &data1, -1);
    if( data == data1 ) {
	row = atoi(gtk_tree_model_get_string_from_iter(model, &iter));
    }
    valid = gtk_tree_model_iter_next (model, &iter);
  }

  if (row<0)
  {

    glb_num_row++;


    row = glb_num_row-1;


    glb_pass_list=g_list_append(glb_pass_list, data);


    if (ini->save_on_add)
	passfile_save(glb_filename);
  }
  else
  {

    if (ini->save_on_change)
	passfile_save(glb_filename);
  }


  fpm_clist_populate_cat_list();
 return 0;
}

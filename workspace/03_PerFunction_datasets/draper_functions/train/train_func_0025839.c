boolean (const std::string name,
		     const std::string description,
		     bool value,
		     bool advanced)
{
  GtkWidget *widget = NULL;
  BooleanSubmitter *submitter = NULL;

  grow_fields (advanced);

  widget = gtk_check_button_new_with_label (description.c_str ());
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), value);
  if (advanced) {

    gtk_table_attach_defaults (GTK_TABLE (advanced_fields), widget,
			       0, 2, advanced_rows -1, advanced_rows);
  } else {

    gtk_table_attach_defaults (GTK_TABLE (fields), widget,
			       0, 2, rows -1, rows);
  }

  submitter = new BooleanSubmitter (name, description, advanced, widget);
  submitters.push_back (submitter);
}

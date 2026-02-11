p_pw_fmac_entry_update_cb(GtkWidget *widget, GapStbPropWidget *pw)
{
  if(pw == NULL) { return; }
  if(pw->stb_elem_refptr == NULL) { return; }
  if(pw->stb_refptr)
  {
    p_pw_push_undo_and_set_unsaved_changes(pw);
  }

  if(pw->stb_elem_refptr->filtermacro_file)
  {
    g_free(pw->stb_elem_refptr->filtermacro_file);
  }

  pw->stb_elem_refptr->filtermacro_file = g_strdup(gtk_entry_get_text(GTK_ENTRY(widget)));

  p_pw_check_fmac_sensitivity(pw);

}

ComposeWindow_set_modified(clawsmail_ComposeWindowObject *self, PyObject *args)
{
  char modified = 0;
  gboolean old_modified;

  if(!PyArg_ParseTuple(args, "b", &modified))
    return NULL;

  old_modified = self->compose->modified;

  self->compose->modified = (modified != 0);


  if((strcmp(gtk_window_get_title(GTK_WINDOW(self->compose->window)), _("Compose message")) != 0) &&
      (old_modified != self->compose->modified)) {
      gchar *str;
      gchar *edited;
      gchar *subject;

      edited = self->compose->modified  ? _(" [Edited]") : "";
      subject = gtk_editable_get_chars(GTK_EDITABLE(self->compose->subject_entry), 0, -1);
      if(subject && strlen(subject))
        str = g_strdup_printf(_("%s - Compose message%s"),
            subject, edited);
      else
        str = g_strdup_printf(_("[no subject] - Compose message%s"), edited);
      gtk_window_set_title(GTK_WINDOW(self->compose->window), str);
      g_free(str);
      g_free(subject);
  }

  flush_gtk_queue();

  Py_INCREF(Py_None);
  return Py_None;
}

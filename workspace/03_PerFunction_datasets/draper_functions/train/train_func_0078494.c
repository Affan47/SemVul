ComposeWindow_save_message_to(clawsmail_ComposeWindowObject *self, PyObject *args)
{
  PyObject *arg;

  if(!PyArg_ParseTuple(args, "O", &arg))
    return NULL;

  if(PyString_Check(arg)) {
    GtkEditable *editable;
    gint pos;

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self->compose->savemsg_checkbtn), TRUE);

    editable = GTK_EDITABLE(gtk_bin_get_child(GTK_BIN(self->compose->savemsg_combo)));
    gtk_editable_delete_text(editable, 0, -1);
    gtk_editable_insert_text(editable, PyString_AsString(arg), -1, &pos);
  }
  else if(clawsmail_folder_check(arg)) {
    GtkEditable *editable;
    gint pos;

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self->compose->savemsg_checkbtn), TRUE);

    editable = GTK_EDITABLE(gtk_bin_get_child(GTK_BIN(self->compose->savemsg_combo)));
    gtk_editable_delete_text(editable, 0, -1);
    gtk_editable_insert_text(editable, folder_item_get_identifier(clawsmail_folder_get_item(arg)), -1, &pos);
  }
  else if (arg == Py_None){

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self->compose->savemsg_checkbtn), FALSE);
  }
  else {
    PyErr_SetString(PyExc_TypeError, "function takes exactly one argument which may be a folder object, a string, or None");
    return NULL;
  }

  flush_gtk_queue();

  Py_INCREF(Py_None);
  return Py_None;
}

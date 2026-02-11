s_object_replace_attrib_in_object(TOPLEVEL *toplevel,
				       OBJECT *o_current,
				       char *new_attrib_name,
				       char *new_attrib_value,
				       gint visibility,
				       gint show_name_value)
{
  GList *a_iter;
  OBJECT *a_current;
  char *old_attrib_text;
  char *old_attrib_name;
  char *new_attrib_text;


  a_iter = o_current->attribs;
  while (a_iter != NULL) {
    a_current = a_iter->data;
    if (a_current->type == OBJ_TEXT
	&& a_current->text != NULL) {


      old_attrib_text = g_strdup(a_current->text->string);
      old_attrib_name = u_basic_breakup_string(old_attrib_text, '=', 0);

      if (strcmp(old_attrib_name, new_attrib_name) == 0) {

	new_attrib_text = g_strconcat(new_attrib_name, "=", new_attrib_value, NULL);
	g_free(a_current->text->string);
	a_current->text->string = g_strdup(new_attrib_text);
	if (visibility != LEAVE_VISIBILITY_ALONE)
	  o_set_visibility (toplevel, a_current, visibility);
	if (show_name_value != LEAVE_NAME_VALUE_ALONE)
	  a_current->show_name_value = show_name_value;
	g_free(new_attrib_text);
	g_free(old_attrib_text);
	g_free(old_attrib_name);
	return;
      } else {
	g_free(old_attrib_text);
	g_free(old_attrib_name);
      }
    }

    a_iter = g_list_next (a_iter);
  }


  fprintf(stderr,
	 "In s_object_replace_attrib_in_object, we have failed to find the attrib %s on the component.  Exiting . . .\n",
	 new_attrib_name);
  exit(-1);
}

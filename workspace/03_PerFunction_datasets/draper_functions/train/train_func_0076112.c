aboutXML_element(GMarkupParseContext *context _U_,
			     const gchar         *element_name,
			     const gchar        **attribute_names,
			     const gchar        **attribute_values,
			     gpointer             user_data,
			     GError             **error _U_)
{
  GtkTextBuffer *text;
  GtkTextIter iter;
  gchar **version, **refVersion;
  int minor, refMinor, i;

  g_return_if_fail(user_data);
  text = GTK_TEXT_BUFFER(user_data);

  DBG_fprintf(stderr, "ChangeLog parser: found '%s' element.\n", element_name);
  if (!strcmp(element_name, PICK_PARSER_ELEMENT_MILESTONE))
    {
      startAbout = FALSE;

      for (i = 0; attribute_names[i]; i++)
	{
	  if (!strcmp(attribute_names[i], PICK_PARSER_ATTRIBUTES_VERSION))
	    {
	      refVersion = g_strsplit_set(VISU_VERSION, ".-", 4);
	      version    = g_strsplit_set(attribute_values[i], ".", 3);
	      refMinor   = (atoi(refVersion[2]) == 99)?
		atoi(refVersion[1]) + 1:atoi(refVersion[1]);
	      minor      = (version[1])?atoi(version[1]):-1;
	      startAbout = (minor == refMinor);
	      g_strfreev(version);
	      g_strfreev(refVersion);
	    }
	}
    }
  else if (!strcmp(element_name, PICK_PARSER_ELEMENT_ENTRY))
    {
      if (startAbout)
	{

	  for (i = 0; attribute_names[i]; i++)
	    {
	      if (!strcmp(attribute_names[i], PICK_PARSER_ATTRIBUTES_TITRE))
		{
		  gtk_text_buffer_get_end_iter(text, &iter);
		  gtk_text_buffer_insert_with_tags_by_name(text, &iter,
							   attribute_values[i],
							   -1, "bold", NULL);
		  gtk_text_buffer_get_end_iter(text, &iter);
		  gtk_text_buffer_insert(text, &iter, _(":\n\n"), -1);
		}
	    }
	}
    }
  else if (!strcmp(element_name, PICK_PARSER_ELEMENT_LI))
    {
      if (startAbout)
	{
	  gtk_text_buffer_get_end_iter(text, &iter);
	  gtk_text_buffer_insert(text, &iter, "\342\200\242\t", -1);


	  for (i = 0; attribute_names[i]; i++)
	    {
	      if (!strcmp(attribute_names[i], PICK_PARSER_ATTRIBUTES_TYPE))
		{
		  gtk_text_buffer_get_end_iter(text, &iter);
		  gtk_text_buffer_insert_with_tags_by_name(text, &iter,
							   attribute_values[i],
							   -1, "italic", NULL);
		  gtk_text_buffer_get_end_iter(text, &iter);
		  gtk_text_buffer_insert(text, &iter, _(": "), -1);
		}
	    }
	  startLi = TRUE;
	}
    }
}

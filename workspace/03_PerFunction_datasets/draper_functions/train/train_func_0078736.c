s_check_oldslot (const GList *obj_list, SYMCHECK *s_current)
{
  const GList *iter;
  char *ptr;
  int found_old = FALSE;
  int number_counter = 0;
  char *message;

  for (iter = obj_list; iter != NULL; iter = g_list_next (iter)) {
    OBJECT *o_current = iter->data;

    if (o_current->type == OBJ_TEXT)
    {
      if (strstr(o_current->text->string, "slot"))
      {

        ptr = o_current->text->string + 4;

        found_old = FALSE;
        number_counter = 0;
        while (ptr && *ptr > '0' && *ptr < '9')
        {
          number_counter++;
          ptr++;
        }

        if (ptr && *ptr == '=')
        {
          found_old++;
        }

        if (!ptr)
          continue;


        if (number_counter == 0)
          continue;


        ptr++;

        while ((ptr && (*ptr > '0') && (*ptr < '9')) || (*ptr == ','))
        {
          ptr++;
        }

        if (*ptr == '\0')
        {
          found_old++;
        }


        if (found_old == 2)
        {
          message = g_strdup_printf (
            "Found old slot#=# attribute: %s\n",
            o_current->text->string);
          s_current->error_messages = g_list_append(s_current->error_messages,
                                                    message);
          s_current->found_oldslot_attrib += found_old;
          s_current->error_count++;

        }
      }
    }
  }
}

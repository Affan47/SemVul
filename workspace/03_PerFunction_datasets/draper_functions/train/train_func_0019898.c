where_is_internal (Keymap map, InfoCommand *cmd)
{
#if defined(INFOKEY)

  register FUNCTION_KEYSEQ *k;

  for (k = cmd->keys; k; k = k->next)
    if (k->map == map)
      return pretty_keyseq (k->keyseq);

  return NULL;

#else


  register int i;


  for (i = 0; i < 256; i++)
    if ((map[i].type == ISFUNC) && map[i].function == cmd)
      {
        sprintf (where_is_rep + where_is_rep_index, "%s", pretty_keyname (i));
        return where_is_rep;
      }


  for (i = 0; i < 256; i++)
    {
      if (map[i].type == ISKMAP)
        {
          int saved_index = where_is_rep_index;
          char *rep;

          sprintf (where_is_rep + where_is_rep_index, "%s ",
                   pretty_keyname (i));

          where_is_rep_index = strlen (where_is_rep);
          rep = where_is_internal ((Keymap)map[i].function, cmd);

          if (rep)
            return where_is_rep;

          where_is_rep_index = saved_index;
        }
    }

  return NULL;

#endif
}

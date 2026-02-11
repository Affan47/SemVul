info_indices_of_file_buffer (FILE_BUFFER *file_buffer)
{
  register int i;
  REFERENCE **result = NULL;


  if (!file_buffer)
    return NULL;


  free (initial_index_filename);
  free (initial_index_nodename);
  initial_index_filename = NULL;
  initial_index_nodename = NULL;

  if (index_nodenames)
    {
      for (i = 0; index_nodenames[i]; i++)
        {
          free (index_nodenames[i]->name);
          free (index_nodenames[i]);
        }

      index_nodenames_index = 0;
      index_nodenames[0] = NULL;
    }


  if (file_buffer->tags)
    {
      TAG *tag;

      for (i = 0; (tag = file_buffer->tags[i]); i++)
        {
          if (string_in_line ("Index", tag->nodename) != -1)
            {
              NODE *node;
              REFERENCE **menu;


              node = info_get_node (tag->filename, tag->nodename,
                                    PARSE_NODE_VERBATIM);
              if (!node)
                continue;


              initial_index_filename = xstrdup (file_buffer->filename);
              initial_index_nodename = xstrdup (tag->nodename);

              menu = info_menu_of_node (node);


              if (menu)
                {
                  add_index_to_index_nodenames (menu, node);


                  result = info_concatenate_references (result, menu);
                }
              free (node);
            }
        }
    }


  for (i = 0; result && result[i]; i++)
    if (!result[i]->filename)
      result[i]->filename = xstrdup (file_buffer->filename);

  return result;
}

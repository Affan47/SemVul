index_entry_exists (WINDOW *window, char *string)
{
  register int i;
  FILE_BUFFER *fb;


  if (!string)
    return 0;

  fb = file_buffer_of_window (window);
  if (!initial_index_filename ||
      !fb ||
      (FILENAME_CMP (initial_index_filename, fb->filename) != 0))
    {
      info_free_references (index_index);
      index_index = info_indices_of_file_buffer (fb);
    }


  if (!index_index)
    return 0;

  for (i = 0; (i > -1) && (index_index[i]); i++)
    if (strcmp (string, index_index[i]->label) == 0)
      break;


  if ((i < 0) || (!index_index[i]))
    {
      for (i = 0; (i > -1) && (index_index[i]); i++)
        if (string_in_line (string, index_index[i]->label) != -1)
          break;

      if ((i > -1) && (index_index[i]))
        string_in_line (string, index_index[i]->label);
    }


  if ((i < 0) || (!index_index[i]))
    return 0;

  return 1;
}

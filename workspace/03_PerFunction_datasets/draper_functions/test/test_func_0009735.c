ifile_read_word_entry (char * line, ifile_db * idata)
{
  db_word_entry * wentry = malloc(sizeof(db_word_entry));
  char *token = NULL;
  long int folder, freq;
  long int num_folders = idata->num_folders;
  extendable_array * freq_array;


  wentry->freq = (extendable_array *) malloc(sizeof(extendable_array));
  freq_array = wentry->freq;
  EXT_ARRAY_INIT_N_SET((*freq_array), long int, num_folders, 0);

  token = strtok(line, " \t");


  if (token == NULL)
    {
      free(wentry);
      free(freq_array);
      return 0;
    }


  htable_put(&(idata->data), (void *) (token), (void *) wentry);
  wentry->word = ifile_strdup(token);


  token = strtok(NULL, " \t");
  if (token != NULL)
    wentry->age = atoi(token);
  else
    wentry->age = 0;


  token = strtok(NULL, ":");
  while (token != NULL)
    {
      folder = atoi(token);
      token = strtok(NULL, " \t");
      if (token != NULL)
	{
	  freq = atoi(token);
	  wentry->tot_freq += freq;
	  EXT_ARRAY_SET((*freq_array), long int, folder, freq);
	}
      token = strtok(NULL, ":");
    }
  return 1;
}

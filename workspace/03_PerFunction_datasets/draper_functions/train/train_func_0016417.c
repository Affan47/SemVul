locate(int script, char* lookup_proc)
{
  if (rinfo[script] == NULL)
    return 0;

  int save_current  = rinfo[script]->current;
  int save_cur_line = rinfo[script]->cur_line;
  int save_cur_col  = rinfo[script]->cur_col;
  int save_debug_line = rinfo[script]->debug_line;
  rinfo[script]->current  = 0;
  rinfo[script]->cur_line = 1;
  rinfo[script]->cur_col  = 0;
  rinfo[script]->debug_line = 1;

  char* line = NULL;
  char* word = NULL;

  while((line = read_next_line(script)) != NULL)
    {
      strip_beginning_spaces(line);

      int is_proc = 0;
      word = get_word(line, 1);
      if (compare(word, "VOID"))
	is_proc = 1;
      free(word);
      if (is_proc)
	{
	  char* cur_proc = NULL;
	  word = get_word(line, 2);
	  cur_proc = separate_string(word, 1, '(');
	  free(word);

	  int is_right_proc = 0;
	  if (compare(cur_proc, lookup_proc))
	    is_right_proc = 1;
	  free(cur_proc);

	  if (is_right_proc)
	    {

	      if (rinfo[script]->sprite != 1000)
		{
		  spr[rinfo[script]->sprite].move_active = 0;
		  if (dversion >= 108)
		    spr[rinfo[script]->sprite].move_nohard = 0;
		}
	      rinfo[script]->skipnext = 0;
	      rinfo[script]->onlevel = 0;
	      rinfo[script]->level = 0;

	      free(line);
	      return 1;

	    }
	}
      free(line);
    }


  rinfo[script]->current  = save_current;
  rinfo[script]->cur_line = save_cur_line;
  rinfo[script]->cur_col  = save_cur_col;
  rinfo[script]->debug_line = save_debug_line;
  return 0;
}

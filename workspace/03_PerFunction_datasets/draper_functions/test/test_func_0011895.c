parse_entry_id (code, pos)
     char *code;
     EB_Position *pos;
{
  EB_Error_Code error_code = EB_SUCCESS;

  if (strchr (code, ':') != NULL) {


    char *endp;
    pos->page = strtol (code, &endp, 0);
    if (*endp != ':')
      goto illegal;

    pos->offset = strtol (endp + 1, &endp, 0);
    if (*endp != '\0')
      goto illegal;

    return 1;

  illegal:
    xprintf ("Illegal position: %s\n", code);
    return 0;

  } else {


    int num, count;
    const char *pattern = variable_ref ("_last_search_pattern");
    EB_Hit list[MAX_HIT_SIZE];

    if (!pattern) {
      xputs ("No search has been executed yet.");
      return 0;
    }
    if ((count = atoi (code) - 1) < 0) {
      xprintf ("Invalid entry number: %s\n", code);
      return 0;
    }
    if (check_subbook ()) {
      error_code = last_search_function (&current_book, pattern);
      if (EB_SUCCESS != error_code) {
	xprintf ("An error occured in parse_entry_id: %s\n",
		eb_error_message (error_code));
	set_error_message (error_code);
	return 0;
      }
      while (EB_SUCCESS == eb_hit_list (&current_book, MAX_HIT_SIZE, list,
					&num) && 0 < num) {
	qsort(list, num, sizeof(EB_Hit), hitcomp);
	if (count < num) {
	  pos->page = list[count].text.page;
	  pos->offset = list[count].text.offset;
	  return 1;
	}
	count -= num;
	pattern = NULL;
      }
      if (num == 0)
	xprintf ("Too big: %s\n", code);
    }
    return 0;
  }
}

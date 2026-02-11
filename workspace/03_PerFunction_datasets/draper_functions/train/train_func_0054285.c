new_local_string(char *s)
#else
new_local_string(s)
	char *s;
#endif
{
  int count = strlen(s) + 1;
  int orig_top = loc_str_top;
  loc_str_top += count;
  if(loc_str_top > STRSPACESZ) {
    StrSpace *new_loc_strspace;
    new_loc_strspace = (StrSpace *)malloc(sizeof(StrSpace));
    if(new_loc_strspace == (StrSpace *)NULL) {
      oops_message(OOPS_FATAL,line_num,NO_COL_NUM,
		   "Cannot alloc space for local strings");
      return (char *)NULL;
    }
    else {
      new_loc_strspace->next = (StrSpace *)NULL;
      curr_loc_strspace->next = new_loc_strspace;
    }
    curr_loc_strspace = curr_loc_strspace->next;
    extra_locstrspace += orig_top;
    orig_top = 0;
    loc_str_top = count;
  }
  return strcpy(curr_loc_strspace->strspace+orig_top,s);
}

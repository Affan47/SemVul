etpan_address_list_write(FILE * f, int * col,
    struct mailimf_address_list * addr_list)
{
  clistiter * cur;
  int r;
  int first;

  first = 1;

  for(cur = clist_begin(addr_list->ad_list) ; cur != NULL ;
      cur = clist_next(cur)) {
    struct mailimf_address * addr;

    addr = clist_content(cur);

    if (!first) {
      r = mailimf_string_write(f, col, ", ", 2);
      if (r != MAILIMF_NO_ERROR)
	return ERROR_FILE;
    }
    else {
      first = 0;
    }

    r = etpan_address_write(f, col, addr);
    if (r != NO_ERROR)
      return r;
  }

  return NO_ERROR;
}

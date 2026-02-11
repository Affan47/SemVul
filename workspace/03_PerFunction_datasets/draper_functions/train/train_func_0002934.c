eblook_search_multi(book, pattern)
     EB_Book *book;
     const char *pattern;
{
  char *candidate[EB_MAX_MULTI_ENTRIES+2];
  EB_Error_Code error_code;
  char *p = strdup(pattern);
  int i;
  int multi_id = atoi(variable_ref("multi-search-id")) - 1;

#ifdef EBLOOK_SEARCH_MULTI_DEBUG
  xprintf("multi_id = %d\n", multi_id);
#endif

  candidate[0] = strtok(p, ":");

  for (i=1; i<EB_MAX_MULTI_ENTRIES+2; i++) {
    candidate[i] = strtok(0, ":");
  }

  for (i=0; i<EB_MAX_MULTI_ENTRIES+2; i++) {
    if (candidate[i] && 0 == strcmp(candidate[i], "*")) {
      candidate[i] = "";
    }
#ifdef EBLOOK_SEARCH_MULTI_DEBUG
    xprintf("candidate[%d] = %s\n", i, candidate[i]);
#endif
  }

  error_code = eb_search_multi(book, multi_id,
    (const char * const *)candidate);

#ifdef EBLOOK_SEARCH_MULTI_DEBUG
  xprintf("return = %d(%s)\n", error_code, eb_error_message(error_code));
#endif

  free(p);
  return error_code;
}

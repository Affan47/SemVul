mkshort_new_handle()
#endif
{
  int i;
  mkshort_handle_imp* h = (mkshort_handle_imp*) xxcalloc(sizeof *h, 1, file, line);

  for (i = 0; i < PRIME; i++) {
    QUEUE_INIT(&h->namelist[i]);
  }

  h->whitespaceok = 1;
  h->badchars = xstrdup(DEFAULT_BADCHARS);
  h->target_len = DEFAULT_TARGET_LEN;
  h->must_uniq = 1;
  h->defname = xstrdup("WPT");
  h->is_utf8 = (global_opts.charset == &cet_cs_vec_utf8);

  return h;
}

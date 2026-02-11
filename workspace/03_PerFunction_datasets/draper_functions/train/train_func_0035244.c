mail_flags_dup(struct mail_flags * flags)
{
  clist * list;
  struct mail_flags * new_flags;
  int r;
  clistiter * cur;

  list = clist_new();
  if (list == NULL) {
    goto err;
  }

  for(cur = clist_begin(flags->fl_extension) ; cur != NULL ;
      cur = clist_next(cur)) {
    char * ext;
    char * original_ext;

    original_ext = clist_content(cur);
    ext = strdup(original_ext);
    if (ext == NULL) {
      goto free;
    }

    r = clist_append(list, ext);
    if (r < 0) {
      free(ext);
      goto free;
    }
  }

  new_flags = mail_flags_new(flags->fl_flags, list);
  if (new_flags == NULL) {
    goto free;
  }

  return new_flags;

 free:
  clist_foreach(list, (clist_func) free, NULL);
  clist_free(list);
 err:
  return NULL;
}

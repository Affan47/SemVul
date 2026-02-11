generic_flags_read(MMAPString * mmapstr, size_t * indx,
			      struct mail_flags ** result)
{
  clist * ext;
  int r;
  struct mail_flags * flags;
  uint32_t value;
  int res;

  r = mailimf_cache_int_read(mmapstr, indx, &value);
  if (r != MAIL_NO_ERROR) {
    res = r;
    goto err;
  }

  ext = NULL;
  r = flags_extension_read(mmapstr, indx, &ext);
  if (r != MAIL_NO_ERROR) {
    res = r;
    goto err;
  }

  flags = mail_flags_new(value, ext);
  if (flags == NULL) {
    res = r;
    goto free;
  }

  * result = flags;

  return MAIL_NO_ERROR;

 free:
  clist_foreach(ext, (clist_func) free, NULL);
  clist_free(ext);
 err:
  return res;
}

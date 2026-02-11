tar_open(TAR **t, char *pathname, tartype_t *type,
   int oflags, int mode, int options)
{
  int res;
  if (tar_init(t, pathname, type, oflags, mode, options) == -1)
    return -1;

  if ((options & TAR_NOOVERWRITE) && (oflags & O_CREAT))
    oflags |= O_EXCL;

#ifdef O_BINARY
  oflags |= O_BINARY;
#endif

  res = (*((*t)->type->openfunc))((*t)->type->call_data, pathname, oflags, mode);
  if (res == -1)
  {
    free(*t);
    return -1;
  }

  return 0;
}

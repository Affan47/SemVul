is_sysrooted_pathname (const char *name)
{
  char *realname;
  int len;
  bfd_boolean result;

  if (ld_canon_sysroot == NULL)
    return FALSE;

  realname = lrealpath (name);
  len = strlen (realname);
  result = FALSE;
  if (len > ld_canon_sysroot_len
      && IS_DIR_SEPARATOR (realname[ld_canon_sysroot_len]))
    {
      realname[ld_canon_sysroot_len] = '\0';
      result = FILENAME_CMP (ld_canon_sysroot, realname) == 0;
    }

  free (realname);
  return result;
}

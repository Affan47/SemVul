list_item_verbose(FILE *out, struct archive_entry *entry)
{
  char                   tmp[100];
  size_t                         w;
  const char            *p;
  const char            *fmt;
  time_t                         tim;
  static time_t          now;
  size_t u_width = 6;
  size_t gs_width = 13;


  if (!now)
    {
    time(&now);
    }
  fprintf(out, "%s %d ",
          archive_entry_strmode(entry),
          archive_entry_nlink(entry));


  p = archive_entry_uname(entry);
  if ((p == NULL) || (*p == '\0'))
    {
    sprintf(tmp, "%lu ",
            (unsigned long)archive_entry_uid(entry));
    p = tmp;
    }
  w = strlen(p);
  if (w > u_width)
    {
    u_width = w;
    }
  fprintf(out, "%-*s ", (int)u_width, p);

  p = archive_entry_gname(entry);
  if (p != NULL && p[0] != '\0')
    {
    fprintf(out, "%s", p);
    w = strlen(p);
    }
  else
    {
    sprintf(tmp, "%lu",
            (unsigned long)archive_entry_gid(entry));
    w = strlen(tmp);
    fprintf(out, "%s", tmp);
    }


  if (archive_entry_filetype(entry) == AE_IFCHR
      || archive_entry_filetype(entry) == AE_IFBLK)
    {
    sprintf(tmp, "%lu,%lu",
            (unsigned long)archive_entry_rdevmajor(entry),
            (unsigned long)archive_entry_rdevminor(entry));
    }
  else
    {


    sprintf(tmp, BSDTAR_FILESIZE_PRINTF,
            (BSDTAR_FILESIZE_TYPE)archive_entry_size(entry));
    }
  if (w + strlen(tmp) >= gs_width)
    {
    gs_width = w+strlen(tmp)+1;
    }
  fprintf(out, "%*s", (int)(gs_width - w), tmp);


  tim = archive_entry_mtime(entry);
#define HALF_YEAR (time_t)365 * 86400 / 2
#if defined(_WIN32) && !defined(__CYGWIN__)

#define DAY_FMT  "%d"
#else
#define DAY_FMT  "%e"
#endif
  if (tim < now - HALF_YEAR || tim > now + HALF_YEAR)
    {
    fmt = DAY_FMT " %b  %Y";
    }
  else
    {
    fmt = DAY_FMT " %b %H:%M";
    }
  strftime(tmp, sizeof(tmp), fmt, localtime(&tim));
  fprintf(out, " %s ", tmp);
  fprintf(out, "%s", archive_entry_pathname(entry));


  if (archive_entry_hardlink(entry))
    {
    fprintf(out, " link to %s",
            archive_entry_hardlink(entry));
    }
  else if (archive_entry_symlink(entry))
    {
    fprintf(out, " -> %s", archive_entry_symlink(entry));
    }
}

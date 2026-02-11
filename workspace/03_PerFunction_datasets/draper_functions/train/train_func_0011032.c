show(char type, int dir, const char* filename,
		 unsigned uid, unsigned gid, unsigned mode,
		 const char* endline)
{
  showmode(type, mode);

  if (uid == (unsigned)-1)
    obuf_puts(&outbuf, UID_NA);
  else
    obuf_putf(&outbuf, "\\ 8d", uid);
  if (gid == (unsigned)-1)
    obuf_puts(&outbuf, UID_NA);
  else
    obuf_putf(&outbuf, "\\ 8d", gid);

  obuf_putc(&outbuf, ' ');
  if (filename[0] != '/') {
    obuf_puts(&outbuf, install_prefix);
    if (dentries[dir].s[0] != '/')
      obuf_putc(&outbuf, '/');
    obuf_putstr(&outbuf, &dentries[dir]);
    obuf_putc(&outbuf, '/');
  }
  obuf_puts(&outbuf, filename);
  obuf_puts(&outbuf, endline);
}

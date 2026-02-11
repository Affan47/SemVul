printstream (DISPLAY *dp)
{
  extern int termwidth;
  FTSENT *p;
  int col;
  int extwidth;

  extwidth = 0;
  if (f_inode)
    extwidth += dp->s_inode + 1;
  if (f_size)
    extwidth += dp->s_block + 1;
  if (f_type)
    extwidth += 1;

  for (col = 0, p = dp->list; p != NULL; p = p->fts_link)
    {
      if (IS_NOPRINT (p))
	continue;
      if (col > 0)
	{
	  putchar (','), col++;
	  if (col + 1 + extwidth + p->fts_namelen >= termwidth)
	    putchar ('\n'), col = 0;
	  else
	    putchar (' '), col++;
	}
      col += printaname (p, dp->s_inode, dp->s_block);
    }
  putchar ('\n');
}

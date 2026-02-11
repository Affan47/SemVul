count() {
  int		i;
  int		fcount;
  const char	*filename;


  filename = fileName->value();

  if (!(type_ & MULTI)) {

    if (!filename || !filename[0]) return 0;
    else return 1;
  }

  for (i = 1, fcount = 0; i <= fileList->size(); i ++)
    if (fileList->selected(i)) {


	fcount ++;
    }

  if (fcount) return fcount;
  else if (!filename || !filename[0]) return 0;
  else return 1;
}

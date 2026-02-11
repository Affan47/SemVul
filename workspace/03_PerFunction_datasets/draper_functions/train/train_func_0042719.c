del_lines()
{ int i;
  varname vn;
  for (i=proc_to; i>del_to; i--)
  { sprintf(vn,"=cline%d",i);
    deletename(vn);
    sprintf(vn,"=clstr%d",i);
    deletename(vn);
  }
  del_to = proc_to;
}

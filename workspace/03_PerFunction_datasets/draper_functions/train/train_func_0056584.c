make_list(struct column_info **ds, struct file_info *fs,
	int nimported)
{
  int i,imp=0;
  char **string;
  Object o;

  string = (char **)DXAllocate(sizeof(char *) * nimported);
  for (i=0; i<fs->ncolumns; i++) {
    if (fs->which[i] == ON){
      string[imp] = (char *)DXAllocate(sizeof(char) * (1+strlen(ds[i]->name)));
      strcpy(string[imp],ds[i]->name);
      imp++;
    }
  }
  o = (Object)DXMakeStringListV(nimported,string);
  if (!o)
    goto error;

  for (i=0; i<nimported; i++)
    DXFree(string[i]);
  DXFree(string);

  return o;

error:
  for (i=0; i<nimported; i++)
    DXFree(string[i]);
  DXFree(string);
  return NULL;
}

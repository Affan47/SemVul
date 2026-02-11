cbf_find_local_tag (cbf_handle handle, const char *tag)
{
  cbf_node *node;

  size_t catlen, collen;

  char categoryname[81];

  char columnname[81];

  char *colstart;

  if (!handle || !tag) return CBF_ARGUMENT;

  if (strlen(tag)>80) return CBF_ARGUMENT;

  if (tag[0] == '_') tag++;

  if (!(colstart = strchr(tag,'.'))) {

    colstart=(char *)tag-1;

    catlen = 0;

  } else {

    catlen = colstart-tag;

  }
  if (catlen) strncpy(categoryname,tag,catlen);

  categoryname[catlen] = '\0';

  collen = (tag+strlen(tag))-colstart;

  columnname[0] = '_';

  if (collen) strncpy(columnname+(catlen?0:1),colstart+1,collen);

  columnname[collen+(catlen?0:1)] = '\0';

  if (cbf_find_parent (&node, handle->node, CBF_SAVEFRAME))
  {

  cbf_failnez (cbf_find_parent (&node, handle->node, CBF_DATABLOCK))

  }

  cbf_failnez(cbf_srch_tag(handle, node, categoryname, columnname))

  return 0;

}

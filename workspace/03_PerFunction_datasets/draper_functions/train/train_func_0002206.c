infoFormat(struct parse_state *ps)
{
  char *p;

  if (!FileTok(ps,"=, \n\t",NO_NEWLINE,&p)) {
	DXAddMessage("#10865","format");
	goto error;
  }

  if (!p){
	DXSetError(ERROR_DATA_INVALID,"#10865","format");
        goto error;
  }
  if (!get_format(ps,&p,&_dxd_gi_format,&_dxd_gi_byteorder))
     goto error;
  if (_dxd_gi_format < 0){
     DXSetError(ERROR_BAD_PARAMETER,"#10862","format",p);
     goto error;
  }

  return OK;
error:
  return ERROR;
}

VgetBinaryData(FILE *fp, void **data, int size)
{
  int j, s, len, step;
  char	*op;
  struct header rec_sep;

  for(j=0; j<_dxd_gi_numflds; j++)
    {
      size = _dxfnumGridPoints(j);
      for (s = 0; s < _dxd_gi_series; s++)
	{
	  step = s*_dxd_gi_numflds;
	  len = _dxd_gi_var[j]->databytes * _dxd_gi_var[j]->datadim * size;
	  if (_dxd_gi_whichser[s] == OFF || _dxd_gi_whichflds[j] == OFF)
	    {
	      if(!(skip_bdata(fp, len))) {
 	        op = "read";
		goto error;
  	      }
	    }
	  else if(!doread(data[step+j], 1, len, fp)) {
 	    op = "read";
	    goto error;
	  }
          if ((_dxd_gi_series-1) != s && !skip_header(fp,&_dxd_gi_serseparat)){
             op = "read series header";
             goto error;
          }
	}
                    rec_sep = _dxd_gi_var[j]->rec_separat[0];
                    if (!skip_header(fp,&rec_sep)){
                       op = " record separator";
                       goto error;
                    }
    }
  return OK;

error:
  if (_dxd_gi_series > 1)
    DXAddMessage("\nTrying to %s field '%s' of series %d",op,_dxd_gi_var[j]->name,s+1);
  else
    DXAddMessage("\nTrying to %s field '%s'",op,_dxd_gi_var[j]->name);
  return ERROR;
}

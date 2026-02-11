skip_bdata(FILE *fp, int toskip)
{

  if (_dxd_gi_format == BINARY && toskip != 0) {
      if (fseek(fp, toskip, 1) != 0) {
          DXSetError(ERROR_MISSING_DATA,"#10911",
			ftell(fp) + toskip);
	  goto error;
	}
    }

  return OK;

 error:
  return ERROR;
}

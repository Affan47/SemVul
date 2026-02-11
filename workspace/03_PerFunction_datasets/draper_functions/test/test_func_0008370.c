_SQLFreeHandle_DESC (
  SQLSMALLINT		  handleType,
  SQLHANDLE		  handle)
{
  DESC (pdesc, handle);
  CONN (pdbc, pdesc->hdbc);
  HPROC hproc;
  RETCODE retcode = SQL_SUCCESS;
  DESC_t *curr_desc;

  if (IS_VALID_HSTMT (pdesc->hstmt))
    {
      PUSHSQLERR (pdesc->herr, en_HY017);
      return SQL_ERROR;
    }
  CLEAR_ERRORS (pdesc);


  curr_desc = (DESC_t *) pdbc->hdesc;
  while (curr_desc)
    {
      if (curr_desc == pdesc)
	{
	  pdbc->hdesc = pdesc->next;
	  break;
	}
      if (curr_desc->next == pdesc)
	{
	  curr_desc->next = pdesc->next;
	  break;
	}
      curr_desc = curr_desc->next;
    }
  if (!curr_desc)
    return SQL_INVALID_HANDLE;


  hproc = SQL_NULL_HPROC;
  if (pdesc->dhdesc)
    {
      hproc = _iodbcdm_getproc (pdbc, en_FreeHandle);
      if (hproc == SQL_NULL_HPROC)
	{
	  PUSHSQLERR (pdesc->herr, en_IM001);
	  retcode = SQL_ERROR;
	}
      else
	CALL_DRIVER (pdbc, pdesc, retcode, hproc,
	    (handleType, pdesc->dhdesc));
    }

  _iodbcdm_freesqlerrlist (pdesc->herr);


  pdesc->type = 0;

  return retcode;
}

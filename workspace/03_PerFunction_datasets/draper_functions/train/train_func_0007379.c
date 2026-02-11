_iodbcdm_UnBindColumn (STMT_t *pstmt, BIND_t *pbind)
{
  PBLST pNewNextBind;
  PBLST *pBindHistory;


  if (pstmt->st_pbinding == NULL)
    return 0;

  for (pBindHistory = &pstmt->st_pbinding; (*pBindHistory);
      pBindHistory = &(*pBindHistory)->bl_nextBind)
    {


      if ((*pBindHistory)->bl_bind.bn_col == pbind->bn_col)
	{
	  pNewNextBind = (*pBindHistory)->bl_nextBind;
	  free (*pBindHistory);
	  (*pBindHistory) = pNewNextBind;
	  return 0;
	}
    }
  return 0;
}

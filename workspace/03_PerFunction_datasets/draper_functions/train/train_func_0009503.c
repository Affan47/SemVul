_iodbcdm_dllclose (HDLL hdll)
{
  dlproc_t *pDrv = NULL, *p;


  for (p = pRoot; p; p = p->next)
    {
      if (p->dll == hdll)
	{
	  pDrv = p;
	  break;
	}
    }


  if (!pDrv)
    return -1;


  pDrv->refcount--;


  if (pDrv->refcount == 0 && pDrv->safe_unload)
    {
      DLL_CLOSE (pDrv->dll);
      pDrv->dll = NULL;
    }

  return 0;
}

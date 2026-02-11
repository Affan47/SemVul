reshGetElem(const char *caller, cdiResH resH, resOps *ops)
{
  listElem_t *listElem;
  int nsp;
  namespaceTuple_t nspT;
  xassert ( ops );

  LIST_INIT();

  LIST_LOCK();

  nsp = namespaceGetActive ();

  nspT = namespaceResHDecode ( resH );

  if (nspT.nsp == nsp &&
      nspT.idx >= 0 &&
      nspT.idx < resHList[nsp].size)
    {
      listElem = resHList[nsp].resources + nspT.idx;
      LIST_UNLOCK();
    }
  else
    {
      LIST_UNLOCK();
      xabortC(caller, "Invalid namespace %d or index %d for resource handle %d when using namespace %d of size %d!",
              nspT.nsp, nspT.idx, (int)resH, nsp, resHList[nsp].size);
    }

  if ( !(listElem && listElem->ops == ops) )
    xabortC(caller, "Invalid resource handle %d, list element not found!",
            (int)resH);
  return listElem;
}

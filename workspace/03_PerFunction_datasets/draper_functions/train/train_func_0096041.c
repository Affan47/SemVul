soap_next_block(struct soap *soap, struct soap_blist *b)
{ char *p;
  if (!b)
    b = soap->blist;
  p = b->ptr;
  if (p)
  { DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Next block\n"));
    b->ptr = *(char**)p;
    SOAP_FREE(soap, p);
    if (b->ptr)
      return b->ptr + sizeof(char*) + sizeof(size_t);
  }
  return NULL;
}

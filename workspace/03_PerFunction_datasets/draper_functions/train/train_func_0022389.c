soap_pop_namespace(struct soap *soap)
{ register struct soap_nlist *np, *nq;
  for (np = soap->nlist; np && np->level >= soap->level; np = nq)
  { nq = np->next;
    DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Pop namespace binding (level=%u) '%s'\n", soap->level, np->id));
    SOAP_FREE(soap, np);
  }
  soap->nlist = np;
}

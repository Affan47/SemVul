soap_wsrm_num_free(struct soap *soap, struct soap_wsrm_sequence *seq)
{ DBGFUN("soap_wsrm_num_free");
  if (seq)
  { struct soap_wsrm_range *p, *q;
    for (p = seq->ranges; p; p = q)
    { q = p->next;
      free((void*)p);
    }
  }
  seq->ranges = NULL;
}

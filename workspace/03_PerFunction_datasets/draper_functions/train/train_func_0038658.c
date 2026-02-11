svc_register (SVCXPRT * xprt, rpcprog_t prog, rpcvers_t vers,
	      void (*dispatch) (struct svc_req *, SVCXPRT *),
	      rpcproc_t protocol)
{
  struct svc_callout *prev;
  register struct svc_callout *s;

  if ((s = svc_find (prog, vers, &prev)) != NULL_SVC)
    {
      if (s->sc_dispatch == dispatch)
	goto pmap_it;
      return FALSE;
    }
  s = (struct svc_callout *) mem_alloc (sizeof (struct svc_callout));
  if (s == (struct svc_callout *) 0)
    return FALSE;

  s->sc_prog = prog;
  s->sc_vers = vers;
  s->sc_dispatch = dispatch;
  s->sc_next = svc_head;
  s->sc_mapped = FALSE;
  svc_head = s;

pmap_it:

  if (protocol)
    {
      if (! pmap_set (prog, vers, protocol, xprt->xp_port))
	return FALSE;

      s->sc_mapped = TRUE;
    }

  return TRUE;
}

m_get_context(pIIR_SingleIndexedAssociation ia, ContextInfo &ctxt, RegionStack &rstack,
	      bool target, int level)
{
  if (ia->index != NULL)
    get_context(ia->index, ctxt, rstack, false, level);
  get_context(ia->value, ctxt, rstack, false, level);

  return NULL;
}

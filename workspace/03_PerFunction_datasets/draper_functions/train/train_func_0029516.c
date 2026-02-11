lookup(Var_ns *root, char *ns)
{
  char *n;
  Var_ns *v;

  if (ns == NULL) {
#ifdef DEFAULT_NAMESPACE
	n = DEFAULT_NAMESPACE;
#else
	log_msg((LOG_ERROR_LEVEL,
			 "Invalid variable reference: namespace is required"));
	return(NULL);
#endif
  }
  else
	n = ns;

  if (!var_ns_is_valid_namespace_name(n))
	return(NULL);

  for (v = root; v != NULL; v = v->next) {
	if (streq(n, v->ns))
	  return(v);
  }

  return(NULL);
}

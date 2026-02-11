var_ns_is_readonly(Var_ns *root, char *ns_name)
{
  Var_ns *ns;

  if ((ns = var_ns_lookup(root, ns_name)) == NULL)
	return(0);

  return((ns->flags & VAR_NS_READONLY) != 0);
}

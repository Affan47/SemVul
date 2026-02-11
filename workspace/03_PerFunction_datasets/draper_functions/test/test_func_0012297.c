push_nested_namespace (tree ns)
{
  if (ns == global_namespace)
    push_to_top_level ();
  else
    {
      push_nested_namespace (CP_DECL_CONTEXT (ns));
      push_namespace (DECL_NAME (ns));
    }
}

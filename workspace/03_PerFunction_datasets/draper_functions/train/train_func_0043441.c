check_template_shadow (tree decl)
{
  tree olddecl;


  if (!current_template_parms)
    return true;


  if (TREE_CODE (decl) == OVERLOAD)
    decl = OVL_CURRENT (decl);
  olddecl = innermost_non_namespace_value (DECL_NAME (decl));


  if (!olddecl)
    return true;


  if (!DECL_P (olddecl) || !DECL_TEMPLATE_PARM_P (olddecl))
    return true;


  if (decl == olddecl
      || TEMPLATE_PARMS_FOR_INLINE (current_template_parms))
    return true;


  if (DECL_SELF_REFERENCE_P (decl))
    return false;

  error ("declaration of %q+#D", decl);
  error (" shadows template parm %q+#D", olddecl);
  return false;
}

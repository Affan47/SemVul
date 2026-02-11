cxx_make_type (enum tree_code code)
{
  tree t = make_node (code);


  if (IS_AGGR_TYPE_CODE (code)
      || code == BOUND_TEMPLATE_TEMPLATE_PARM)
    {
      struct lang_type *pi;

      pi = ggc_alloc_cleared (sizeof (struct lang_type));

      TYPE_LANG_SPECIFIC (t) = pi;
      pi->u.c.h.is_lang_type_class = 1;

#ifdef GATHER_STATISTICS
      tree_node_counts[(int)lang_type] += 1;
      tree_node_sizes[(int)lang_type] += sizeof (struct lang_type);
#endif
    }


  if (IS_AGGR_TYPE_CODE (code))
    {
      SET_CLASSTYPE_INTERFACE_UNKNOWN_X (t, interface_unknown);
      CLASSTYPE_INTERFACE_ONLY (t) = interface_only;


      build_pointer_type (t);
    }
  else


    TYPE_ALIAS_SET (t) = 0;


  if (IS_AGGR_TYPE_CODE (code) || code == TEMPLATE_TYPE_PARM
      || code == BOUND_TEMPLATE_TEMPLATE_PARM
      || code == TYPENAME_TYPE)
    TYPE_BINFO (t) = make_binfo (size_zero_node, t, NULL_TREE, NULL_TREE);

  return t;
}

begin_class_definition (tree t)
{
  if (error_operand_p (t) || error_operand_p (TYPE_MAIN_DECL (t)))
    return error_mark_node;

  if (processing_template_parmlist)
    {
      error ("definition of %q#T inside template parameter list", t);
      return error_mark_node;
    }


  if (TREE_CODE (t) == RECORD_TYPE
      && !processing_template_decl)
    {
      tree ns = TYPE_CONTEXT (t);
      if (ns && TREE_CODE (ns) == NAMESPACE_DECL
	  && DECL_CONTEXT (ns) == std_node
	  && DECL_NAME (ns)
	  && !strcmp (IDENTIFIER_POINTER (DECL_NAME (ns)), "decimal"))
	{
	  const char *n = TYPE_NAME_STRING (t);
	  if ((strcmp (n, "decimal32") == 0)
	      || (strcmp (n, "decimal64") == 0)
	      || (strcmp (n, "decimal128") == 0))
	    TYPE_TRANSPARENT_AGGR (t) = 1;
	}
    }


  else if (TREE_CODE (t) == TYPENAME_TYPE)
    {
      error ("invalid definition of qualified type %qT", t);
      t = error_mark_node;
    }

  if (t == error_mark_node || ! MAYBE_CLASS_TYPE_P (t))
    {
      t = make_class_type (RECORD_TYPE);
      pushtag (make_anon_name (), t, ts_current);
    }

  if (TYPE_BEING_DEFINED (t))
    {
      t = make_class_type (TREE_CODE (t));
      pushtag (TYPE_IDENTIFIER (t), t, ts_current);
    }
  maybe_process_partial_specialization (t);
  pushclass (t);
  TYPE_BEING_DEFINED (t) = 1;

  if (flag_pack_struct)
    {
      tree v;
      TYPE_PACKED (t) = 1;


      for (v = TYPE_NEXT_VARIANT (t); v; v = TYPE_NEXT_VARIANT (v))
	TYPE_PACKED (v) = 1;
    }


  if (! TYPE_ANONYMOUS_P (t))
    {
      struct c_fileinfo *finfo = get_fileinfo (input_filename);
      CLASSTYPE_INTERFACE_ONLY (t) = finfo->interface_only;
      SET_CLASSTYPE_INTERFACE_UNKNOWN_X
	(t, finfo->interface_unknown);
    }
  reset_specialization();


  build_self_reference ();

  return t;
}

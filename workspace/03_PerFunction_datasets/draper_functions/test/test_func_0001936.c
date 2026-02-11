redeclare_class_template (tree type, tree parms)
{
  tree tmpl;
  tree tmpl_parms;
  int i;

  if (!TYPE_TEMPLATE_INFO (type))
    {
      error ("%qT is not a template type", type);
      return false;
    }

  tmpl = TYPE_TI_TEMPLATE (type);
  if (!PRIMARY_TEMPLATE_P (tmpl))


    return true;

  if (!parms)
    {
      error ("template specifiers not specified in declaration of %qD",
	     tmpl);
      return false;
    }

  parms = INNERMOST_TEMPLATE_PARMS (parms);
  tmpl_parms = DECL_INNERMOST_TEMPLATE_PARMS (tmpl);

  if (TREE_VEC_LENGTH (parms) != TREE_VEC_LENGTH (tmpl_parms))
    {
      error_n (input_location, TREE_VEC_LENGTH (parms),
               "redeclared with %d template parameter",
               "redeclared with %d template parameters",
               TREE_VEC_LENGTH (parms));
      inform_n (input_location, TREE_VEC_LENGTH (tmpl_parms),
                "previous declaration %q+D used %d template parameter",
                "previous declaration %q+D used %d template parameters",
                tmpl, TREE_VEC_LENGTH (tmpl_parms));
      return false;
    }

  for (i = 0; i < TREE_VEC_LENGTH (tmpl_parms); ++i)
    {
      tree tmpl_parm;
      tree parm;
      tree tmpl_default;
      tree parm_default;

      if (TREE_VEC_ELT (tmpl_parms, i) == error_mark_node
          || TREE_VEC_ELT (parms, i) == error_mark_node)
        continue;

      tmpl_parm = TREE_VALUE (TREE_VEC_ELT (tmpl_parms, i));
      if (tmpl_parm == error_mark_node)
	return false;

      parm = TREE_VALUE (TREE_VEC_ELT (parms, i));
      tmpl_default = TREE_PURPOSE (TREE_VEC_ELT (tmpl_parms, i));
      parm_default = TREE_PURPOSE (TREE_VEC_ELT (parms, i));


      if (TREE_CODE (tmpl_parm) != TREE_CODE (parm)
	  || (TREE_CODE (tmpl_parm) != TYPE_DECL
	      && !same_type_p (TREE_TYPE (tmpl_parm), TREE_TYPE (parm)))
	  || (TREE_CODE (tmpl_parm) != PARM_DECL
	      && (TEMPLATE_TYPE_PARAMETER_PACK (TREE_TYPE (tmpl_parm))
		  != TEMPLATE_TYPE_PARAMETER_PACK (TREE_TYPE (parm))))
	  || (TREE_CODE (tmpl_parm) == PARM_DECL
	      && (TEMPLATE_PARM_PARAMETER_PACK (DECL_INITIAL (tmpl_parm))
		  != TEMPLATE_PARM_PARAMETER_PACK (DECL_INITIAL (parm)))))
	{
	  error ("template parameter %q+#D", tmpl_parm);
	  error ("redeclared here as %q#D", parm);
	  return false;
	}

      if (tmpl_default != NULL_TREE && parm_default != NULL_TREE)
	{


	  error_at (input_location, "redefinition of default argument for %q#D", parm);
	  inform (DECL_SOURCE_LOCATION (tmpl_parm),
		  "original definition appeared here");
	  return false;
	}

      if (parm_default != NULL_TREE)


	TREE_PURPOSE (TREE_VEC_ELT (tmpl_parms, i)) = parm_default;
      else if (tmpl_default != NULL_TREE)


	TREE_PURPOSE (TREE_VEC_ELT (parms, i)) = tmpl_default;
    }

    return true;
}

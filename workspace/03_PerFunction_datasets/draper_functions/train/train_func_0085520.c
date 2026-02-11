find_substitution (tree node)
{
  int i;
  const int size = vec_safe_length (G.substitutions);
  tree decl;
  tree type;

  if (DEBUG_MANGLE)
    fprintf (stderr, "  ++ find_substitution (%s at %p)\n",
	     tree_code_name[TREE_CODE (node)], (void *) node);


  node = canonicalize_for_substitution (node);


  decl = TYPE_P (node) ? TYPE_NAME (node) : node;
  type = TYPE_P (node) ? node : TREE_TYPE (node);


  if (decl
      && is_std_substitution (decl, SUBID_ALLOCATOR)
      && !CLASSTYPE_USE_TEMPLATE (TREE_TYPE (decl)))
    {
      write_string ("Sa");
      return 1;
    }


  if (decl && is_std_substitution (decl, SUBID_BASIC_STRING))
    {
      if (TYPE_P (node))
	{


	  if (cp_type_quals (type) == TYPE_UNQUALIFIED
	      && CLASSTYPE_USE_TEMPLATE (type))
	    {
	      tree args = CLASSTYPE_TI_ARGS (type);
	      if (TREE_VEC_LENGTH (args) == 3
		  && same_type_p (TREE_VEC_ELT (args, 0), char_type_node)
		  && is_std_substitution_char (TREE_VEC_ELT (args, 1),
					       SUBID_CHAR_TRAITS)
		  && is_std_substitution_char (TREE_VEC_ELT (args, 2),
					       SUBID_ALLOCATOR))
		{
		  write_string ("Ss");
		  return 1;
		}
	    }
	}
      else

	{
	  write_string ("Sb");
	  return 1;
	}
    }


  if (TYPE_P (node)
      && cp_type_quals (type) == TYPE_UNQUALIFIED
      && CLASS_TYPE_P (type)
      && CLASSTYPE_USE_TEMPLATE (type)
      && CLASSTYPE_TEMPLATE_INFO (type) != NULL)
    {


      tree args = CLASSTYPE_TI_ARGS (type);
      if (TREE_VEC_LENGTH (args) == 2
	  && TYPE_P (TREE_VEC_ELT (args, 0))
	  && same_type_p (TREE_VEC_ELT (args, 0), char_type_node)
	  && is_std_substitution_char (TREE_VEC_ELT (args, 1),
				       SUBID_CHAR_TRAITS))
	{

	  if (is_std_substitution (decl, SUBID_BASIC_ISTREAM))
	    {
	      write_string ("Si");
	      return 1;
	    }

	  else if (is_std_substitution (decl, SUBID_BASIC_OSTREAM))
	    {
	      write_string ("So");
	      return 1;
	    }

	  else if (is_std_substitution (decl, SUBID_BASIC_IOSTREAM))
	    {
	      write_string ("Sd");
	      return 1;
	    }
	}
    }


  if (decl && DECL_NAMESPACE_STD_P (decl))
    {
      write_string ("St");
      return 1;
    }


  for (i = 0; i < size; ++i)
    {
      tree candidate = (*G.substitutions)[i];


      if (decl == candidate
	  || (TYPE_P (candidate) && type && TYPE_P (node)
	      && same_type_p (type, candidate))
	  || NESTED_TEMPLATE_MATCH (node, candidate))
	{
	  write_substitution (i);
	  return 1;
	}
    }


  return 0;
}

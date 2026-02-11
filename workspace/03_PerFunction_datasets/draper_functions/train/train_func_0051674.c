tree_size (tree node)
{
  enum tree_code code = TREE_CODE (node);

  switch (TREE_CODE_CLASS (code))
    {
    case 'd':
      return sizeof (struct tree_decl);

    case 't':
      return sizeof (struct tree_type);

    case 'b':
      return sizeof (struct tree_block);

    case 'r':
    case 'e':
    case 's':
    case '<':
    case '1':
    case '2':
      return (sizeof (struct tree_exp)
	      + TREE_CODE_LENGTH (code) * sizeof (char *) - sizeof (char *));

    case 'c':
      switch (code)
	{
	case INTEGER_CST:	return sizeof (struct tree_int_cst);
	case REAL_CST:		return sizeof (struct tree_real_cst);
	case COMPLEX_CST:	return sizeof (struct tree_complex);
	case VECTOR_CST:	return sizeof (struct tree_vector);
	case STRING_CST:	return sizeof (struct tree_string);
	default:
	  return (*lang_hooks.tree_size) (code);
	}

    case 'x':
      switch (code)
	{
	case IDENTIFIER_NODE:	return lang_hooks.identifier_size;
	case TREE_LIST:		return sizeof (struct tree_list);
	case TREE_VEC:		return (sizeof (struct tree_vec)
					+ TREE_VEC_LENGTH(node) * sizeof(char *)
					- sizeof (char *));

	case ERROR_MARK:
	case PLACEHOLDER_EXPR:	return sizeof (struct tree_common);

	default:
	  return (*lang_hooks.tree_size) (code);
	}

    default:
      abort ();
    }
}

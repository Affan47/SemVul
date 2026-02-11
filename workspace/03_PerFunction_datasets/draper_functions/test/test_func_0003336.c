get_enclosing_class (tree type)
{
  tree node = type;

  while (node && TREE_CODE (node) != NAMESPACE_DECL)
    {
      switch (TREE_CODE_CLASS (TREE_CODE (node)))
	{
	case 'd':
	  node = DECL_CONTEXT (node);
	  break;

	case 't':
	  if (node != type)
	    return node;
	  node = TYPE_CONTEXT (node);
	  break;

	default:
	  abort ();
	}
    }
  return NULL_TREE;
}

find_abi_tags_r (tree *tp, int *, void *data)
{
  if (!TAGGED_TYPE_P (*tp))
    return NULL_TREE;

  if (tree attributes = lookup_attribute ("abi_tag", TYPE_ATTRIBUTES (*tp)))
    {
      struct abi_tag_data *p = static_cast<struct abi_tag_data*>(data);
      for (tree list = TREE_VALUE (attributes); list;
	   list = TREE_CHAIN (list))
	{
	  tree tag = TREE_VALUE (list);
	  tree id = get_identifier (TREE_STRING_POINTER (tag));
	  if (!IDENTIFIER_MARKED (id))
	    {
	      if (TYPE_P (p->subob))
		{
		  warning (OPT_Wabi_tag, "%qT does not have the %E abi tag "
			   "that base %qT has", p->t, tag, p->subob);
		  inform (location_of (p->subob), "%qT declared here",
			  p->subob);
		}
	      else
		{
		  warning (OPT_Wabi_tag, "%qT does not have the %E abi tag "
			   "that %qT (used in the type of %qD) has",
			   p->t, tag, *tp, p->subob);
		  inform (location_of (p->subob), "%qD declared here",
			  p->subob);
		  inform (location_of (*tp), "%qT declared here", *tp);
		}
	    }
	}
    }
  return NULL_TREE;
}

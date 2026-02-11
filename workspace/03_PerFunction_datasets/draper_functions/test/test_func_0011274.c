has_addr_references_p (struct cgraph_node *node,
		       void *data ATTRIBUTE_UNUSED)
{
  int i;
  struct ipa_ref *ref;

  for (i = 0; ipa_ref_list_referring_iterate (&node->symbol.ref_list,
					     i, ref); i++)
    if (ref->use == IPA_REF_ADDR)
      return true;
  return false;
}

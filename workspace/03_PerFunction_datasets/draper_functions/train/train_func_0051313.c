can_remove_node_now_p_1 (struct cgraph_node *node)
{


  return (!node->address_taken
	  && !ipa_ref_has_aliases_p (&node->ref_list)
	  && cgraph_can_remove_if_no_direct_calls_p (node)


	  && !DECL_VIRTUAL_P (node->decl)


	  && !cgraph_new_nodes);
}

stable_node_chain_remove_range(struct stable_node *stable_node,
					   unsigned long start_pfn,
					   unsigned long end_pfn,
					   struct rb_root *root)
{
	struct stable_node *dup;
	struct hlist_node *hlist_safe;

	if (!is_stable_node_chain(stable_node)) {
		VM_BUG_ON(is_stable_node_dup(stable_node));
		return stable_node_dup_remove_range(stable_node, start_pfn,
						    end_pfn);
	}

	hlist_for_each_entry_safe(dup, hlist_safe,
				  &stable_node->hlist, hlist_dup) {
		VM_BUG_ON(!is_stable_node_dup(dup));
		stable_node_dup_remove_range(dup, start_pfn, end_pfn);
	}
	if (hlist_empty(&stable_node->hlist)) {
		free_stable_node_chain(stable_node, root);
		return true;
	} else
		return false;
}

remove_node_from_stable_tree(struct stable_node *stable_node)
{
	struct rmap_item *rmap_item;


	BUG_ON(stable_node->rmap_hlist_len < 0);

	hlist_for_each_entry(rmap_item, &stable_node->hlist, hlist) {
		if (rmap_item->hlist.next)
			ksm_pages_sharing--;
		else
			ksm_pages_shared--;
		VM_BUG_ON(stable_node->rmap_hlist_len <= 0);
		stable_node->rmap_hlist_len--;
		put_anon_vma(rmap_item->anon_vma);
		rmap_item->address &= PAGE_MASK;
		cond_resched();
	}


#if GCC_VERSION >= 40903
	BUILD_BUG_ON(STABLE_NODE_DUP_HEAD <= &migrate_nodes);
	BUILD_BUG_ON(STABLE_NODE_DUP_HEAD >= &migrate_nodes + 1);
#endif

	if (stable_node->head == &migrate_nodes)
		list_del(&stable_node->list);
	else
		stable_node_dup_del(stable_node);
	free_stable_node(stable_node);
}

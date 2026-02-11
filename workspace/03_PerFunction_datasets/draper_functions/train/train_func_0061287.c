free_extent_state(struct extent_state *state)
{
	if (!state)
		return;
	if (atomic_dec_and_test(&state->refs)) {
		WARN_ON(extent_state_in_tree(state));
		btrfs_leak_debug_del(&state->leak_list);
		trace_free_extent_state(state, _RET_IP_);
		kmem_cache_free(extent_state_cache, state);
	}
}

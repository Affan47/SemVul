write_hints(struct dm_cache_metadata *cmd, struct dm_cache_policy *policy)
{
	int r;

	r = begin_hints(cmd, policy);
	if (r) {
		DMERR("begin_hints failed");
		return r;
	}

	return policy_walk_mappings(policy, save_hint, cmd);
}

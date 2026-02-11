ocfs2_queue_replay_slots(struct ocfs2_super *osb,
		enum ocfs2_orphan_reco_type orphan_reco_type)
{
	struct ocfs2_replay_map *replay_map = osb->replay_map;
	int i;

	if (!replay_map)
		return;

	if (replay_map->rm_state != REPLAY_NEEDED)
		return;

	for (i = 0; i < replay_map->rm_slots; i++)
		if (replay_map->rm_replay_slots[i])
			ocfs2_queue_recovery_completion(osb->journal, i, NULL,
							NULL, NULL,
							orphan_reco_type);
	replay_map->rm_state = REPLAY_DONE;
}

ocfs2_node_map_test_bit(struct ocfs2_super *osb,
			    struct ocfs2_node_map *map,
			    int bit)
{
	int ret;
	if (bit >= map->num_nodes) {
		mlog(ML_ERROR, "bit=%d map->num_nodes=%d\n", bit, map->num_nodes);
		BUG();
	}
	spin_lock(&osb->node_map_lock);
	ret = test_bit(bit, map->map);
	spin_unlock(&osb->node_map_lock);
	return ret;
}

append_stats(struct stats_candidate *stats_queue, struct tree_node *node, int stats_count,
	     int max_count, path_t start_path, path_t max_path, int min_increment, struct board *b)
{


	for (struct tree_node *ni = node->children; ni; ni = ni->sibling) {

		if (is_pass(node_coord(ni))) continue;
		if (ni->hints & TREE_HINT_INVALID) continue;

		int incr = ni->u.playouts - ni->pu.playouts;
		if (incr < min_increment) continue;


		if (stats_count >= max_count) {
			if (DEBUGL(0))
				fprintf(stderr, "*** stats overflow %d nodes\n", stats_count);
			return stats_count;
		}
		path_t child_path = append_child(start_path, node_coord(ni), b);
		stats_queue[stats_count].playout_incr = incr;
		stats_queue[stats_count].coord_path = child_path;
		stats_queue[stats_count++].node = ni;

		if (incr >= MAX_BUCKETS) incr = MAX_BUCKETS - 1;
		bucket_count[incr]++;


		if (child_path >= max_path) continue;

		stats_count = append_stats(stats_queue, ni, stats_count, max_count,
					   child_path, max_path, min_increment, b);
	}
	return stats_count;
}

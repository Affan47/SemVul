shuffle_node_order(ofps *s) {
	int i;

	for (i = 0; i < s->tinp; i++) {
		swap_nodes(s, i, i_rand(0, s->tinp-1));
	}
}

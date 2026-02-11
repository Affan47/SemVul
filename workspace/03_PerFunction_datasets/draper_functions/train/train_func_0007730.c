dig_which_node(struct Plus_head *plus, double x, double y, double thresh)
{
    register int i;
    register int first_time;
    register int have_match;
    int winner;
    double least_dist, dist;
    P_NODE *node;

    first_time = 1;
    have_match = 0;
    winner = 0;
    least_dist = 0.0;
    for (i = 1; i <= plus->n_nodes; i++) {
	if (plus->Node[i] == NULL)
	    continue;

	node = plus->Node[i];
	if ((fabs(node->x - x) <= thresh) && (fabs(node->y - y) <= thresh)) {
	    dist = dist_squared(x, y, node->x, node->y);
	    if (first_time) {
		least_dist = dist;
		first_time = 0;
		winner = i;
		have_match = 1;
	    }
	    if (dist < least_dist) {
		least_dist = dist;
		winner = i;
	    }
	}
    }

    if (!have_match)
	return (-1);

    return (winner);
}

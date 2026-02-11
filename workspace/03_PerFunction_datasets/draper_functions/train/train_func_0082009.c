edge_multiplicity(struct isl_sched_edge *edge, int carry,
	int use_coincidence)
{
	if (carry && !edge->validity && !edge->conditional_validity)
		return 0;
	if (carry)
		return 1;
	if (edge->proximity || edge->local)
		return 2;
	if (use_coincidence && edge->coincidence)
		return 2;
	if (edge->validity)
		return 1;
	return 0;
}

geo_has_children(double prob_node_has_children)
{
	double rn = (double) rand() / RAND_MAX;

	if (rn <= prob_node_has_children)
		return true;
	else
		return false;
}

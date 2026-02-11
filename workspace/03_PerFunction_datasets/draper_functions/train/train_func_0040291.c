maze_markov_bellman_node_default_create(
	struct maze_markov_state *s,
	enum maze_markov_action a,
	float cost,
	struct maze_markov_bellman_node *n
)
{
	struct maze_markov_bellman_node *ret;
	struct maze_markov_transition_list *tl;

	if (!(tl = MAZE_MARKOV_GET_TRANSITION_LIST(s,a)))
		goto err;

	ret = (struct maze_markov_bellman_node *)
		malloc(sizeof(struct maze_markov_bellman_node));

	ret->action = a;
	ret->cost = cost;
	ret->next = n;

	goto out;
err:
	return 0;
out:
	return ret;
}

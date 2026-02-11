find_blocks(Agraph_t * g, circ_state * state)
{
    Agnode_t *n;
    Agnode_t *root = NULL;
    estack stk;


    if (state->rootname) {
	root = agfindnode(g, state->rootname);
    }
    if (!root && state->N_root) {
	for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
	    if (late_bool(ORIGN(n), state->N_root, 0)) {
		root = n;
		break;
	    }
	}
    }

    if (!root)
	root = agfstnode(g);
    if (Verbose)
	fprintf (stderr, "root = %s\n", agnameof(root));
    stk.sz = 0;
    stk.top = NULL;
    dfs(g, root, state, 1, &stk);

}

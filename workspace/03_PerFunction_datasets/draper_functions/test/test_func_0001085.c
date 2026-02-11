push_state(node_t *node, int state)
{
	if(!statestack)
	{
		statestack = xmalloc(4 * sizeof(*statestack));
		nastatestack = 4;
		nstatestack = 0;
	}
	else if(nstatestack >= nastatestack)
	{
		nastatestack *= 2;
		statestack = xrealloc(statestack, nastatestack * sizeof(*statestack));
	}
	statestack[nstatestack].node = node;
	statestack[nstatestack].state = state;
	nstatestack++;
}

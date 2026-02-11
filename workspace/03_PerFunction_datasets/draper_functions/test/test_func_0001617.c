drawable_reset_group_highlight(GF_TraverseState *tr_state, GF_Node *n)
{
	Drawable *hlight = tr_state->visual->compositor->focus_highlight;
	if (hlight && (n == gf_node_get_private(hlight->node))) gf_node_set_private(hlight->node, NULL);
}

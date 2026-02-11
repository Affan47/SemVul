gf_term_pick_node(GF_Terminal *term, s32 X, s32 Y)
{
	if (!term || !term->compositor) return NULL;
	return gf_sc_pick_node(term->compositor, X, Y);
}

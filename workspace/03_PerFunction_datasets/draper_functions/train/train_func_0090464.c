alloc_vertex(ModeInfo * mi, angle_c dir, fringe_node_c * from, tiling_c * tp)
{
	fringe_node_c *v;

	if ((v = ALLOC_NODE(fringe_node_c)) == NULL) {
		tp->done = True;
		if (MI_IS_VERBOSE(mi)) {
			(void) fprintf(stderr, "No memory in alloc_vertex()\n");
		}
		tp->busyLoop = CELEBRATE;
		return v;
	}
	*v = *from;
	add_unit_vec(dir, v->fived);
	fived_to_loc(v->fived, tp, &(v->loc));
	if (v->loc.x < 0 || v->loc.y < 0
	    || v->loc.x >= tp->width || v->loc.y >= tp->height) {
		v->off_screen = True;
		if (v->loc.x < -tp->width || v->loc.y < -tp->height
		  || v->loc.x >= 2 * tp->width || v->loc.y >= 2 * tp->height)
			tp->done = True;
	} else {
		v->off_screen = False;
		tp->fringe.n_nodes++;
	}
	v->n_tiles = 0;
	v->rule_mask = (1 << N_VERTEX_RULES) - 1;
	v->list_ptr = 0;
	return v;
}

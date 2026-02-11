triangleset2d_check_changes(GF_Node *node, Drawable *stack, GF_TraverseState *tr_state)
{
	if (gf_node_dirty_get(node)) {
		u32 i, count;
		X_TriangleSet2D *p = (X_TriangleSet2D *)node;
		drawable_reset_path(stack);
		count = p->vertices.count;
		while (count%3) count--;
		for (i=0; i<count; i+=3) {
			gf_path_add_move_to(stack->path, p->vertices.vals[i].x, p->vertices.vals[i].y);
			gf_path_add_line_to(stack->path, p->vertices.vals[i+1].x, p->vertices.vals[i+1].y);
			gf_path_add_line_to(stack->path, p->vertices.vals[i+2].x, p->vertices.vals[i+2].y);
			gf_path_close(stack->path);
		}
		gf_node_dirty_clear(node, 0);
		drawable_mark_modified(stack, tr_state);
	}
}

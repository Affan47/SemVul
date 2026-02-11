move_selected_items(double dx, double dy)
{
	FOREACH_ITEM(_selected_items, i) {
		ganv_node_move(*i, dx, dy);
	}
}

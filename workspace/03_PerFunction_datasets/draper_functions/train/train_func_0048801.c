process_outs(node& n) {
	bool alive = remove_vec(n.dst);
	if (alive)
		live_changed = true;
	return alive;
}

visit(repeat_node& n, bool enter) {
	if (enter) {
		live = n.target->live_before;
		process_phi_branch(n.target->loop_phi, n.rep_id);
	} else {
	}
	return true;
}

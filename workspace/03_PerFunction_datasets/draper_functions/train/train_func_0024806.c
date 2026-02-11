close() {
	if(closed)
		return;
	closed = true;
	while(out) {
		Out* tmp = out;
		out = out->next;
		tmp->release();
	}
	close_fd();
	for(Task* child = tree_first_child; child; child = child->tree_next_sibling)
		child->close();
	if(Log(LOG_CONN)) {
		dump_context(stdout);
		fprintf(stdout,"~ closed\n");
		fflush(stdout);
	}
	if(Task* parent = tree_parent) {
		while(parent->tree_parent)
			parent = parent->tree_parent;
		parent->close();
	}
	next_close = scheduler.close_list;
	scheduler.close_list = this;
	unlink_timeout();
	fd = -1;
}

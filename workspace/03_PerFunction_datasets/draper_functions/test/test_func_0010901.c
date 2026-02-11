create_repeat(region_node* target) {
	repeat_node* n = new (pool.allocate(sizeof(repeat_node)))
			repeat_node(target, target->repeats.size() + 1);
	target->repeats.push_back(n);
	all_nodes.push_back(n);
	return n;
}

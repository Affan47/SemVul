register_node_type(void)
{
	int ret;

 	BUILD_BUG_ON(ARRAY_SIZE(node_state_attr) != NR_NODE_STATES);
 	BUILD_BUG_ON(ARRAY_SIZE(node_state_attrs)-1 != NR_NODE_STATES);

	ret = subsys_system_register(&node_subsys, cpu_root_attr_groups);
	if (!ret) {
		static struct notifier_block node_memory_callback_nb = {
			.notifier_call = node_memory_callback,
			.priority = NODE_CALLBACK_PRI,
		};
		register_hotmemory_notifier(&node_memory_callback_nb);
	}


	return ret;
}

add_result(int x, int y)
{
	debug_reuse_check_sub_mode_node(x, y);

	if(num_of_result_node>=result_node_array_def_size)
	{
		result_node_array_def_size += result_node_array_reset_amount;
		path_reuse_result_node_ptr = (ResultNode*) mem_resize(path_reuse_result_node_ptr, sizeof(ResultNode)* result_node_array_def_size);
		cur_result_node_ptr = path_reuse_result_node_ptr+num_of_result_node;
	}

	cur_result_node_ptr->node_x = x;
	cur_result_node_ptr->node_y = y;
	cur_result_node_ptr++;
	num_of_result_node++;
}

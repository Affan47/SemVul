seek_path_offset()
{
	if(!is_leader_path_valid())
		return;

	if(is_node_avail_empty())
	{
		copy_leader_path_offset();
		return;
	}


	result_node_array_def_size += result_node_array_reset_amount;
	path_reuse_result_node_ptr = (ResultNode*) mem_add(sizeof(ResultNode)* result_node_array_def_size);
	memset(path_reuse_result_node_ptr, 0, sizeof(ResultNode)* result_node_array_def_size);
	cur_result_node_ptr = path_reuse_result_node_ptr;
	num_of_result_node = 0;


	add_result(start_x, start_y);


	cur_leader_node_ptr = reuse_leader_path_backup+1;
	cur_leader_node_num = 2;
	use_offset_method(reuse_leader_path_backup[0].node_x, reuse_leader_path_backup[0].node_y);


	ResultNode *lastNode = path_reuse_result_node_ptr + num_of_result_node - 1;
	if((lastNode->node_x!=vir_dest_x || lastNode->node_y!=vir_dest_y) && is_node_avail_empty())
	{
		incomplete_search++;
		reuse_path_status = REUSE_PATH_INCOMPLETE_SEARCH;
	}
}

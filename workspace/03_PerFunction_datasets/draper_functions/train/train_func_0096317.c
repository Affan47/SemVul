set_offset_condition(int startX, int startY, int destX, int destY)
{


	err_when(leader_path_num>=cur_path_num);

	if(cur_path_num>0)
	{

		start_x_offset	= startX - leader_path_start_x;
		start_y_offset	= startY - leader_path_start_y;
		dest_x_offset	= destX - leader_path_dest_x;
		dest_y_offset	= destY - leader_path_dest_y;
	}
	else
	{
		err_when(reuse_path_status != REUSE_PATH_FIRST_SEEK);

		start_x_offset	= start_y_offset = dest_x_offset = dest_y_offset = 0;
		leader_path_start_x = startX;
		leader_path_start_y = startY;
		leader_path_dest_x = destX;
		leader_path_dest_y = destY;

		leader_path_num = cur_path_num;
	}
}

valid_disp_area(int fitInBox)
{


	if( top_x_loc < 0 )
		top_x_loc = 0;

	if( top_y_loc < 0 )
		top_y_loc = 0;

	if( top_x_loc + disp_x_loc > max_x_loc )
		top_x_loc = max_x_loc - disp_x_loc;

	if( top_y_loc + disp_y_loc > max_y_loc )
		top_y_loc = max_y_loc - disp_y_loc;


	if( fitInBox )
	{
		if( cur_x_loc < top_x_loc )
			cur_x_loc = top_x_loc;

		if( cur_x_loc >= top_x_loc + disp_x_loc )
			cur_x_loc = top_x_loc + disp_x_loc - 1;

		if( cur_y_loc < top_y_loc )
			cur_y_loc = top_y_loc;

		if( cur_y_loc >= top_y_loc + disp_y_loc )
			cur_y_loc = top_y_loc + disp_y_loc - 1;
	}
}

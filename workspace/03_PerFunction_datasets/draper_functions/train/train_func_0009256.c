f0r_get_param_info( f0r_param_info_t* info, int param_index )
{
	switch ( param_index ) {
		case 0:
			info->name = "Left";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "";
			break;
		case 1:
			info->name = "Right";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "";
			break;
		case 2:
			info->name = "Top";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "";
			break;
		case 3:
			info->name = "Bottom";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "";
			break;
		case 4:
			info->name = "Invert";
			info->type = F0R_PARAM_BOOL;
			info->explanation = "Invert the mask, creates a hole in the frame.";
			break;
		case 5:
			info->name = "Blur";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "Blur the outline of the mask";
			break;
	}
}

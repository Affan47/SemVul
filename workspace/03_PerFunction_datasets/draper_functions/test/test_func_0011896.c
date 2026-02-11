f0r_get_param_info(f0r_param_info_t* info, int param_index)
{
  switch(param_index)
  {
  case 0:
    info->name = "Map black to";
    info->type = F0R_PARAM_COLOR;
    info->explanation = "The color to map source color with null luminance";
    break;
  case 1:
	  info->name = "Map white to";
	  info->type = F0R_PARAM_COLOR;
	  info->explanation = "The color to map source color with full luminance";
	  break;
  case 2:
	  info->name = "Tint amount";
	  info->type = F0R_PARAM_DOUBLE;
	  info->explanation = "Amount of color";
	  break;
  }
}

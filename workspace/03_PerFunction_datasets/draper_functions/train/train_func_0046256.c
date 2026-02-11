f0r_get_param_info(f0r_param_info_t* info, int param_index)
{
  switch(param_index)
    {
    case 0:
      info->name = "BlockSizeX";
      info->type = F0R_PARAM_DOUBLE;
      info->explanation = "Horizontal size of one \"pixel\"";
      break;
    case 1:
      info->name = "BlockSizeY";
      info->type = F0R_PARAM_DOUBLE;
      info->explanation = "Vertical size of one \"pixel\"";
      break;
    }
}

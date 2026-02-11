decompose_address (struct address_info *info, rtx *loc, enum machine_mode mode,
		   addr_space_t as, enum rtx_code outer_code)
{
  memset (info, 0, sizeof (*info));
  info->mode = mode;
  info->as = as;
  info->addr_outer_code = outer_code;
  info->outer = loc;
  info->inner = strip_address_mutations (loc, &outer_code);
  info->base_outer_code = outer_code;
  switch (GET_CODE (*info->inner))
    {
    case PRE_DEC:
    case PRE_INC:
    case POST_DEC:
    case POST_INC:
      decompose_incdec_address (info);
      break;

    case PRE_MODIFY:
    case POST_MODIFY:
      decompose_automod_address (info);
      break;

    default:
      decompose_normal_address (info);
      break;
    }
}

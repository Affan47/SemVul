pft_fill_overlap_param(struct pf_parameter *parameter,
                                   const struct unit_type *punittype)
{
  switch (utype_move_type(punittype)) {
  case UMT_LAND:
    parameter->get_MC = land_overlap_move;
    parameter->get_TB = dont_cross_ocean;
    break;
  case UMT_SEA:
    parameter->get_MC = sea_overlap_move;
    break;
  case UMT_BOTH:
    parameter->get_MC = airmove;
    break;
  default:
    log_error("pft_fill_overlap_param() impossible move type!");
    break;
  }

  if (!unit_type_really_ignores_zoc(punittype)) {
    parameter->get_zoc = is_my_zoc;
  } else {
    parameter->get_zoc = NULL;
  }
}

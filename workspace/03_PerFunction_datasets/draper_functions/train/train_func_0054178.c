compare_locs (dw_loc_descr_ref x, dw_loc_descr_ref y)
{
  for (; x != NULL && y != NULL; x = x->dw_loc_next, y = y->dw_loc_next)
    if (x->dw_loc_opc != y->dw_loc_opc
	|| x->dtprel != y->dtprel
	|| !compare_loc_operands (x, y))
      break;
  return x == NULL && y == NULL;
}

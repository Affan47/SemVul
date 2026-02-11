operator()(const account_t * left,
					  const account_t * right)
{
  assert(left);
  assert(right);

  account_xdata_t& lxdata(account_xdata(*left));
  if (! (lxdata.dflags & ACCOUNT_SORT_CALC)) {
    guarded_compute(sort_order, lxdata.sort_value, details_t(*left));
    lxdata.dflags |= ACCOUNT_SORT_CALC;
  }

  account_xdata_t& rxdata(account_xdata(*right));
  if (! (rxdata.dflags & ACCOUNT_SORT_CALC)) {
    guarded_compute(sort_order, rxdata.sort_value, details_t(*right));
    rxdata.dflags |= ACCOUNT_SORT_CALC;
  }

  return lxdata.sort_value < rxdata.sort_value;
}

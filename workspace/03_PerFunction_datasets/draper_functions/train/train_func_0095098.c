load_kills_store (rtx x, rtx store_pattern, int after)
{
  if (after)
    return anti_dependence (x, store_pattern);
  else
    return true_dependence (store_pattern, GET_MODE (store_pattern), x,
			    rtx_addr_varies_p);
}

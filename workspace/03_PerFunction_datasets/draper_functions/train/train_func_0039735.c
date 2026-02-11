find_case_label_range (gimple stmt, tree min, tree max, size_t *min_idx,
		       size_t *max_idx)
{
  size_t i, j;
  bool min_take_default = !find_case_label_index (stmt, 1, min, &i);
  bool max_take_default = !find_case_label_index (stmt, i, max, &j);

  if (i == j
      && min_take_default
      && max_take_default)
    {


      *min_idx = 1;
      *max_idx = 0;
      return false;
    }
  else
    {
      bool take_default = min_take_default || max_take_default;
      tree low, high;
      size_t k;

      if (max_take_default)
	j--;


      high = CASE_LOW (gimple_switch_label (stmt, i));
      if (CASE_HIGH (gimple_switch_label (stmt, i)))
	high = CASE_HIGH (gimple_switch_label (stmt, i));
      for (k = i + 1; k <= j; ++k)
	{
	  low = CASE_LOW (gimple_switch_label (stmt, k));
	  if (!integer_onep (int_const_binop (MINUS_EXPR, low, high)))
	    {
	      take_default = true;
	      break;
	    }
	  high = low;
	  if (CASE_HIGH (gimple_switch_label (stmt, k)))
	    high = CASE_HIGH (gimple_switch_label (stmt, k));
	}

      *min_idx = i;
      *max_idx = j;
      return !take_default;
    }
}

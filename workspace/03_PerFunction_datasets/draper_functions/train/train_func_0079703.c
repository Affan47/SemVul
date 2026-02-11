array_index_is_valid(long sb) const
{
      if (sb < s0_ && sb < e0_)
	    return false;
      if (sb > e0_ && sb > s0_)
	    return false;
      return true;
}

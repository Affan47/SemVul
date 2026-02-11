calculate_output(const udp_levels_table&cur,
					   const udp_levels_table&prev,
					   vvp_bit4_t cur_out)
{
      if (cur == prev)
	    return cur_out;

      udp_levels_table cur_tmp = cur;

      unsigned long mask_out = 1UL << port_count();
      switch (cur_out) {
	  case BIT4_0:
	    cur_tmp.mask0 |= mask_out;
	    break;
	  case BIT4_1:
	    cur_tmp.mask1 |= mask_out;
	    break;
	  default:
	    cur_tmp.maskx |= mask_out;
	    break;
      }

      vvp_bit4_t lev = test_levels_(cur_tmp);
      if (lev == BIT4_Z) {
	    lev = test_edges_(cur_tmp, prev);
      }

      return lev;
}

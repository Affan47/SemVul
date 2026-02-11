draw_number_bool64(ivl_expr_t expr)
{
      int res;
      const char*bits = ivl_expr_bits(expr);
      uint64_t val = 0;
      unsigned long idx, low, hig;

      for (idx = 0 ;  idx < ivl_expr_width(expr) ;  idx += 1) {
	    if (bits[idx] == '1')
		  val |= 1UL << idx;
      }

      res = allocate_word();
      low = val % UINT64_C(0x100000000);
      hig = val / UINT64_C(0x100000000);
      fprintf(vvp_out, "   %%ix/load %d, %lu, %lu;\n", res, low, hig);
      return res;
}

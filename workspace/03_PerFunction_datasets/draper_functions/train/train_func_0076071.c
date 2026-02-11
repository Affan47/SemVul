ivl_expr_uvalue(ivl_expr_t net)
{
      switch (net->type_) {

	  case IVL_EX_ULONG:
	    return net->u_.ulong_.value;

	  case IVL_EX_NUMBER: {
		unsigned long val = 0;
		for (unsigned long idx = 0 ;  idx < net->width_ ;  idx += 1) {
		      if (net->u_.number_.bits_[idx] == '1')
			    val |= 1UL << idx;
		}

		return val;
	  }

	  default:
	    assert(0);
      }

      assert(0);
      return 0;
}

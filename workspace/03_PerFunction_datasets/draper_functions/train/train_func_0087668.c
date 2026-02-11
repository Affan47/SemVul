of_CMPZ(vthread_t thr, vvp_code_t cp)
{
      vvp_bit4_t eq = BIT4_1;

      unsigned idx1 = cp->bit_idx[0];
      unsigned idx2 = cp->bit_idx[1];

      for (unsigned idx = 0 ;  idx < cp->number ;  idx += 1) {
	    vvp_bit4_t lv = thr_get_bit(thr, idx1);
	    vvp_bit4_t rv = thr_get_bit(thr, idx2);

	    if ((lv != BIT4_Z) && (rv != BIT4_Z) && (lv != rv)) {
		  eq = BIT4_0;
		  break;
	    }

	    if (idx1 >= 4) idx1 += 1;
	    if (idx2 >= 4) idx2 += 1;
      }

      thr_put_bit(thr, 4, eq);

      return true;
}

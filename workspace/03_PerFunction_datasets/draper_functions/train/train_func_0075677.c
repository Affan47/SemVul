of_LOAD_AVX_P(vthread_t thr, vvp_code_t cp)
{
      unsigned bit = cp->bit_idx[0];
      unsigned index = cp->bit_idx[1];
      unsigned adr = thr->words[3].w_int;


      if (thr_get_bit(thr, 4) == BIT4_1) {
	    thr_put_bit(thr, bit, BIT4_X);
	    return true;
      }

      long use_index = thr->words[index].w_int;

      vvp_vector4_t word = array_get_word(cp->array, adr);

      if ((use_index >= (long)word.size()) || (use_index < 0)) {
	    thr_put_bit(thr, bit, BIT4_X);
      } else {
	    thr_put_bit(thr, bit, word.value(use_index));
      }

      thr->words[index].w_int = use_index + 1;

      return true;
}

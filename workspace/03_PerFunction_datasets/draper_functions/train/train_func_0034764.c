pv_set_bits(pv_s * vec, int bits)
{
	if (bits == vec->bits) return;

	if (bits == FLINT_BITS)
	{
		pv_iter_s iter;
      PV_ITER_INIT(iter, *vec, 0);

		mp_limb_t * temp = (mp_limb_t *) flint_heap_alloc(vec->alloc);

		for (ulong i = 0; i < vec->length; i++)
		   PV_GET_NEXT(temp[i], iter);

		if (vec->entries) flint_heap_free(vec->entries);
		vec->entries = temp;
		vec->alloc = vec->alloc;

		vec->bits = bits;
#if BIT_FIDDLE
		vec->log_bits = FLINT_LG_BITS_PER_LIMB;
		vec->pack = 1;
		vec->log_pack = 0;
#endif
	} else if (vec->bits == FLINT_BITS)
	{
		mp_limb_t * temp = vec->entries;

		ulong limbs = (vec->alloc*bits - 1)/FLINT_BITS + 1;
		vec->entries = (mp_limb_t *) flint_heap_alloc(limbs);
      vec->alloc = (limbs*FLINT_BITS)/bits;

		vec->bits = bits;
#if BIT_FIDDLE
		vec->log_bits = FLINT_BIT_COUNT(bits) - 1;
		vec->pack = FLINT_BITS/bits;
		vec->log_pack = FLINT_BIT_COUNT(vec->pack) - 1;
#endif

		pv_iter_s iter;
      PV_ITER_INIT(iter, *vec, 0);

		for (ulong i = 0; i < vec->length; i++)
		{
			PV_SET_NEXT(iter, temp[i]);
		}

		flint_heap_free(temp);
	} else
	{
		pv_iter_s iter1, iter2;
		PV_ITER_INIT(iter1, *vec, 0);

		ulong limbs = (vec->alloc*bits - 1)/FLINT_BITS + 1;
		vec->entries = (mp_limb_t *) flint_heap_alloc(limbs);
      vec->alloc = (limbs*FLINT_BITS)/bits;

		vec->bits = bits;
#if BIT_FIDDLE
		vec->log_bits = FLINT_BIT_COUNT(bits) - 1;
		vec->pack = FLINT_BITS/bits;
		vec->log_pack = FLINT_BIT_COUNT(vec->pack) - 1;
#endif
		PV_ITER_INIT(iter2, *vec, 0);

      ulong temp;

		for (ulong i = 0; i < vec->length; i++)
		{
			PV_GET_NEXT(temp, iter1);
			PV_SET_NEXT(iter2, temp);
		}

		if (vec->entries) flint_heap_free(iter1.entries);
	}
}

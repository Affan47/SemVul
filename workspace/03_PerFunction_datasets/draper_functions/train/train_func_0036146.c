compressed_rank_query_packed(void * cr_packed, cmph_uint32 idx)
{

	register cmph_uint32 *ptr = (cmph_uint32 *)cr_packed;
	register cmph_uint32 max_val = *ptr++;
	register cmph_uint32 n = *ptr++;
	register cmph_uint32 rem_r = *ptr++;
	register cmph_uint32 buflen_sel = *ptr++;
	register cmph_uint32 * sel_packed = ptr;

	register cmph_uint32 * bits_vec = sel_packed + 2;

	register cmph_uint32 * vals_rems = (ptr += (buflen_sel >> 2));


	register cmph_uint32 rems_mask;
	register cmph_uint32 val_quot, val_rem;
	register cmph_uint32 sel_res, rank;

	if(idx > max_val)
	{
		return n;
	}

	val_quot = idx >> rem_r;
	rems_mask = (1U << rem_r) - 1U;
	val_rem = idx & rems_mask;
	if(val_quot == 0)
	{
		rank = sel_res = 0;
	}
	else
	{
		sel_res = select_query_packed(sel_packed, val_quot - 1) + 1;
		rank = sel_res - val_quot;
	}

	do
	{
		if(GETBIT32(bits_vec, sel_res))
		{
			break;
		}
		if(get_bits_value(vals_rems, rank, rem_r, rems_mask) >= val_rem)
		{
			break;
		}
		sel_res++;
		rank++;
	} while(1);

	return rank;
}

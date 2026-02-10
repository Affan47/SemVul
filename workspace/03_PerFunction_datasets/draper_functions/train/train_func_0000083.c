unroll_hindexed(dtype, data, fl_idx, len, elts)

struct trdtype		**dtype;
char			**data;
int			fl_idx;
int			*len;
int			*elts;

{
	int		i, j;
	int		count;
	int		savaddr;
	int		disp;
	struct trdtype	*savbuff;
	struct trdtype	*idxbuff;

	count = (*dtype)->trd_count;
	idxbuff = ++(*dtype);
	*dtype += count;
	savbuff = *dtype;
	savaddr = address;

	for (i = 0;
	     (i < count) && (*len > 0) && (*elts != 0);
	     ++i, ++idxbuff) {

		disp = idxbuff->trd_disp;
		if (fl_idx) disp = HDISP(disp);

		address = savaddr + idxbuff->trd_disp;

		for (j = 0;
		     (j < idxbuff->trd_length) && (*len > 0) && (*elts != 0);
		     ++j) {
			*dtype = savbuff;
			unroll(dtype, data, len, elts);
		}

		eltcount = 0;
	}
}

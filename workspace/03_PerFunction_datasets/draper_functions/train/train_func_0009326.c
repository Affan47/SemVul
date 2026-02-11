select_affine_point(felem out_x, felem out_y,
				const limb *table, limb index)
{
    limb i, j;

    memset(out_x, 0, sizeof(felem));
    memset(out_y, 0, sizeof(felem));

    for (i = 1; i < 16; i++) {
	limb mask = i ^ index;
	mask |= mask >> 2;
	mask |= mask >> 1;
	mask &= 1;
	mask--;
	for (j = 0; j < NLIMBS; j++, table++) {
	    out_x[j] |= *table & mask;
	}
	for (j = 0; j < NLIMBS; j++, table++) {
	    out_y[j] |= *table & mask;
	}
    }
}

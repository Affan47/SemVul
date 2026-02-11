scalar_base_mult(felem nx, felem ny, felem nz, const u8 scalar[32])
{
    int i, j;
    limb n_is_infinity_mask = -1, p_is_noninfinite_mask, mask;
    u32 table_offset;

    felem px, py;
    felem tx, ty, tz;

    memset(nx, 0, sizeof(felem));
    memset(ny, 0, sizeof(felem));
    memset(nz, 0, sizeof(felem));


    for (i = 0; i < 32; i++) {
	if (i) {
	    point_double(nx, ny, nz, nx, ny, nz);
	}
	table_offset = 0;
	for (j = 0; j <= 32; j += 32) {
	    char bit0 = get_bit(scalar, 31 - i + j);
	    char bit1 = get_bit(scalar, 95 - i + j);
	    char bit2 = get_bit(scalar, 159 - i + j);
	    char bit3 = get_bit(scalar, 223 - i + j);
	    limb index = bit0 | (bit1 << 1) | (bit2 << 2) | (bit3 << 3);

	    select_affine_point(px, py, kPrecomputed + table_offset, index);
	    table_offset += 30 * NLIMBS;


	    point_add_mixed(tx, ty, tz, nx, ny, nz, px, py);


	    copy_conditional(nx, px, n_is_infinity_mask);
	    copy_conditional(ny, py, n_is_infinity_mask);
	    copy_conditional(nz, kOne, n_is_infinity_mask);


	    p_is_noninfinite_mask = NON_ZERO_TO_ALL_ONES(index);
	    mask = p_is_noninfinite_mask & ~n_is_infinity_mask;
	    copy_conditional(nx, tx, mask);
	    copy_conditional(ny, ty, mask);
	    copy_conditional(nz, tz, mask);

	    n_is_infinity_mask &= ~p_is_noninfinite_mask;
	}
    }
}

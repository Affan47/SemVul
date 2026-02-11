__reset_rsvds_bits_mask_ept(struct rsvd_bits_validate *rsvd_check,
			    int maxphyaddr, bool execonly)
{
	u64 bad_mt_xwr;

	rsvd_check->rsvd_bits_mask[0][3] =
		rsvd_bits(maxphyaddr, 51) | rsvd_bits(3, 7);
	rsvd_check->rsvd_bits_mask[0][2] =
		rsvd_bits(maxphyaddr, 51) | rsvd_bits(3, 6);
	rsvd_check->rsvd_bits_mask[0][1] =
		rsvd_bits(maxphyaddr, 51) | rsvd_bits(3, 6);
	rsvd_check->rsvd_bits_mask[0][0] = rsvd_bits(maxphyaddr, 51);


	rsvd_check->rsvd_bits_mask[1][3] = rsvd_check->rsvd_bits_mask[0][3];
	rsvd_check->rsvd_bits_mask[1][2] =
		rsvd_bits(maxphyaddr, 51) | rsvd_bits(12, 29);
	rsvd_check->rsvd_bits_mask[1][1] =
		rsvd_bits(maxphyaddr, 51) | rsvd_bits(12, 20);
	rsvd_check->rsvd_bits_mask[1][0] = rsvd_check->rsvd_bits_mask[0][0];

	bad_mt_xwr = 0xFFull << (2 * 8);
	bad_mt_xwr |= 0xFFull << (3 * 8);
	bad_mt_xwr |= 0xFFull << (7 * 8);
	bad_mt_xwr |= REPEAT_BYTE(1ull << 2);
	bad_mt_xwr |= REPEAT_BYTE(1ull << 6);
	if (!execonly) {

		bad_mt_xwr |= REPEAT_BYTE(1ull << 4);
	}
	rsvd_check->bad_mt_xwr = bad_mt_xwr;
}

bnx2x_init_mac_credit_pool(struct bnx2x *bp,
				struct bnx2x_credit_pool_obj *p, u8 func_id,
				u8 func_num)
{

#define BNX2X_CAM_SIZE_EMUL 5

	int cam_sz;

	if (CHIP_IS_E1(bp)) {

		if (!CHIP_REV_IS_SLOW(bp))
			cam_sz = (MAX_MAC_CREDIT_E1 / 2) - BNX2X_MAX_MULTICAST;
		else
			cam_sz = BNX2X_CAM_SIZE_EMUL - BNX2X_MAX_EMUL_MULTI;

		bnx2x_init_credit_pool(p, func_id * cam_sz, cam_sz);

	} else if (CHIP_IS_E1H(bp)) {


		if ((func_num > 0)) {
			if (!CHIP_REV_IS_SLOW(bp))
				cam_sz = (MAX_MAC_CREDIT_E1H / (2*func_num));
			else
				cam_sz = BNX2X_CAM_SIZE_EMUL;
			bnx2x_init_credit_pool(p, func_id * cam_sz, cam_sz);
		} else {

			bnx2x_init_credit_pool(p, 0, 0);
		}

	} else {


		if (func_num > 0) {
			if (!CHIP_REV_IS_SLOW(bp))
				cam_sz = PF_MAC_CREDIT_E2(bp, func_num);
			else
				cam_sz = BNX2X_CAM_SIZE_EMUL;


			bnx2x_init_credit_pool(p, -1, cam_sz);
		} else {

			bnx2x_init_credit_pool(p, 0, 0);
		}
	}
}

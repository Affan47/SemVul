bnx2x_state_wait(struct bnx2x *bp, int state,
				   unsigned long *pstate)
{

	int cnt = 5000;

	if (CHIP_REV_IS_EMUL(bp))
		cnt *= 20;

	DP(BNX2X_MSG_SP, "waiting for state to become %d\n", state);

	might_sleep();
	while (cnt--) {
		if (!test_bit(state, pstate)) {
#ifdef BNX2X_STOP_ON_ERROR
			DP(BNX2X_MSG_SP, "exit  (cnt %d)\n", 5000 - cnt);
#endif
			return 0;
		}

		usleep_range(1000, 2000);

		if (bp->panic)
			return -EIO;
	}


	BNX2X_ERR("timeout waiting for state %d\n", state);
#ifdef BNX2X_STOP_ON_ERROR
	bnx2x_panic();
#endif

	return -EBUSY;
}

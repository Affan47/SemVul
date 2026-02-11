dp_link_train_cr(struct dp_state *dp)
{
	bool cr_done = false, abort = false;
	int voltage = dp->conf[0] & DPCD_LC03_VOLTAGE_SWING_SET;
	int tries = 0, i;

	dp_set_training_pattern(dp, 1);

	do {
		if (dp_link_train_commit(dp, false) ||
		    dp_link_train_update(dp, false, 100))
			break;

		cr_done = true;
		for (i = 0; i < dp->link_nr; i++) {
			u8 lane = (dp->stat[i >> 1] >> ((i & 1) * 4)) & 0xf;
			if (!(lane & DPCD_LS02_LANE0_CR_DONE)) {
				cr_done = false;
				if (dp->conf[i] & DPCD_LC03_MAX_SWING_REACHED)
					abort = true;
				break;
			}
		}

		if ((dp->conf[0] & DPCD_LC03_VOLTAGE_SWING_SET) != voltage) {
			voltage = dp->conf[0] & DPCD_LC03_VOLTAGE_SWING_SET;
			tries = 0;
		}
	} while (!cr_done && !abort && ++tries < 5);

	return cr_done ? 0 : -1;
}

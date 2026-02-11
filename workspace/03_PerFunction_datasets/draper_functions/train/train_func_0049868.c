do_cal(int start)
{
	char	temp[APC_LBUF];
	int	tval, ret;

	apc_flush(SER_AA);
	ret = apc_write(APC_STATUS);

	if (ret != 1) {
		upslog_with_errno(LOG_ERR, "do_cal: apc_write failed");
		return STAT_INSTCMD_HANDLED;
	}

	ret = apc_read(temp, sizeof(temp), SER_AA);


	if ((ret < 1) || (!strcmp(temp, "NA")))
		return STAT_INSTCMD_HANDLED;

	tval = strtol(temp, 0, 16);

	if (tval & APC_STAT_CAL) {
		if (start == 1) {

			upslogx(LOG_INFO, "runtime calibration already in progress");
			return STAT_INSTCMD_HANDLED;
		}


		upslogx(LOG_INFO, "stopping runtime calibration");

		ret = apc_write(APC_CMD_CALTOGGLE);

		if (ret != 1) {
			upslog_with_errno(LOG_ERR, "do_cal: apc_write failed");
			return STAT_INSTCMD_HANDLED;
		}

		ret = apc_read(temp, sizeof(temp), SER_AA);

		if ((ret < 1) || (!strcmp(temp, "NA")) || (!strcmp(temp, "NO"))) {
			upslogx(LOG_WARNING, "stop calibration failed: %s",
				temp);
			return STAT_INSTCMD_HANDLED;
		}

		return STAT_INSTCMD_HANDLED;
	}


	if (start == 0) {
		upslogx(LOG_INFO, "runtime calibration not occurring");
		return STAT_INSTCMD_HANDLED;
	}

	upslogx(LOG_INFO, "starting runtime calibration");

	ret = apc_write(APC_CMD_CALTOGGLE);

	if (ret != 1) {
		upslog_with_errno(LOG_ERR, "do_cal: apc_write failed");
		return STAT_INSTCMD_HANDLED;
	}

	ret = apc_read(temp, sizeof(temp), SER_AA);

	if ((ret < 1) || (!strcmp(temp, "NA")) || (!strcmp(temp, "NO"))) {
		upslogx(LOG_WARNING, "start calibration failed: %s", temp);
		return STAT_INSTCMD_HANDLED;
	}

	return STAT_INSTCMD_HANDLED;
}

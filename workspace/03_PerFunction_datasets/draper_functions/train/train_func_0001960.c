thermal_init(struct hfi1_devdata *dd)
{
	int ret = 0;

	if (dd->icode != ICODE_RTL_SILICON ||
	    !(dd->flags & HFI1_DO_INIT_ASIC))
		return ret;

	acquire_hw_mutex(dd);
	dd_dev_info(dd, "Initializing thermal sensor\n");


	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x0,
				RESET_SBUS_RECEIVER, 0);
	if (ret) {
		THERM_FAILURE(dd, ret, "Bus Reset");
		goto done;
	}

	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x0,
				WRITE_SBUS_RECEIVER, 0x1);
	if (ret) {
		THERM_FAILURE(dd, ret, "Therm Block Reset");
		goto done;
	}

	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x1,
				WRITE_SBUS_RECEIVER, 0x32);
	if (ret) {
		THERM_FAILURE(dd, ret, "Write Clock Div");
		goto done;
	}

	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x3,
				WRITE_SBUS_RECEIVER,
				SBUS_THERM_MONITOR_MODE);
	if (ret) {
		THERM_FAILURE(dd, ret, "Write Mode Sel");
		goto done;
	}

	ret = sbus_request_slow(dd, SBUS_THERMAL, 0x0,
				WRITE_SBUS_RECEIVER, 0x2);
	if (ret) {
		THERM_FAILURE(dd, ret, "Write Reset Deassert");
		goto done;
	}

	msleep(22);


	write_csr(dd, ASIC_CFG_THERM_POLL_EN, 0x1);
done:
	release_hw_mutex(dd);
	return ret;
}

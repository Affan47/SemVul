pidff_init_fields(struct pidff_device *pidff, struct input_dev *dev)
{
	int envelope_ok = 0;

	if (PIDFF_FIND_FIELDS(set_effect, PID_SET_EFFECT, 1)) {
		hid_err(pidff->hid, "unknown set_effect report layout\n");
		return -ENODEV;
	}

	PIDFF_FIND_FIELDS(block_load, PID_BLOCK_LOAD, 0);
	if (!pidff->block_load[PID_EFFECT_BLOCK_INDEX].value) {
		hid_err(pidff->hid, "unknown pid_block_load report layout\n");
		return -ENODEV;
	}

	if (PIDFF_FIND_FIELDS(effect_operation, PID_EFFECT_OPERATION, 1)) {
		hid_err(pidff->hid, "unknown effect_operation report layout\n");
		return -ENODEV;
	}

	if (PIDFF_FIND_FIELDS(block_free, PID_BLOCK_FREE, 1)) {
		hid_err(pidff->hid, "unknown pid_block_free report layout\n");
		return -ENODEV;
	}

	if (!PIDFF_FIND_FIELDS(set_envelope, PID_SET_ENVELOPE, 1))
		envelope_ok = 1;

	if (pidff_find_special_fields(pidff) || pidff_find_effects(pidff, dev))
		return -ENODEV;

	if (!envelope_ok) {
		if (test_and_clear_bit(FF_CONSTANT, dev->ffbit))
			hid_warn(pidff->hid,
				 "has constant effect but no envelope\n");
		if (test_and_clear_bit(FF_RAMP, dev->ffbit))
			hid_warn(pidff->hid,
				 "has ramp effect but no envelope\n");

		if (test_and_clear_bit(FF_PERIODIC, dev->ffbit))
			hid_warn(pidff->hid,
				 "has periodic effect but no envelope\n");
	}

	if (test_bit(FF_CONSTANT, dev->ffbit) &&
	    PIDFF_FIND_FIELDS(set_constant, PID_SET_CONSTANT, 1)) {
		hid_warn(pidff->hid, "unknown constant effect layout\n");
		clear_bit(FF_CONSTANT, dev->ffbit);
	}

	if (test_bit(FF_RAMP, dev->ffbit) &&
	    PIDFF_FIND_FIELDS(set_ramp, PID_SET_RAMP, 1)) {
		hid_warn(pidff->hid, "unknown ramp effect layout\n");
		clear_bit(FF_RAMP, dev->ffbit);
	}

	if ((test_bit(FF_SPRING, dev->ffbit) ||
	     test_bit(FF_DAMPER, dev->ffbit) ||
	     test_bit(FF_FRICTION, dev->ffbit) ||
	     test_bit(FF_INERTIA, dev->ffbit)) &&
	    PIDFF_FIND_FIELDS(set_condition, PID_SET_CONDITION, 1)) {
		hid_warn(pidff->hid, "unknown condition effect layout\n");
		clear_bit(FF_SPRING, dev->ffbit);
		clear_bit(FF_DAMPER, dev->ffbit);
		clear_bit(FF_FRICTION, dev->ffbit);
		clear_bit(FF_INERTIA, dev->ffbit);
	}

	if (test_bit(FF_PERIODIC, dev->ffbit) &&
	    PIDFF_FIND_FIELDS(set_periodic, PID_SET_PERIODIC, 1)) {
		hid_warn(pidff->hid, "unknown periodic effect layout\n");
		clear_bit(FF_PERIODIC, dev->ffbit);
	}

	PIDFF_FIND_FIELDS(pool, PID_POOL, 0);

	if (!PIDFF_FIND_FIELDS(device_gain, PID_DEVICE_GAIN, 1))
		set_bit(FF_GAIN, dev->ffbit);

	return 0;
}

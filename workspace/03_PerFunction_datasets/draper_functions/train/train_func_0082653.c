au0828_get_key_au8522(struct au0828_rc *ir)
{
	unsigned char buf[40];
	DEFINE_IR_RAW_EVENT(rawir);
	int i, j, rc;
	int prv_bit, bit, width;
	bool first = true;


	if (test_bit(DEV_DISCONNECTED, &ir->dev->dev_state))
		return 0;


	rc = au8522_rc_read(ir, 0xe1, -1, buf, 1);
	if (rc < 0 || !(buf[0] & (1 << 4))) {

		au8522_rc_set(ir, 0xe0, 1 << 4);
		return 0;
	}


	rc = au8522_rc_read(ir, 0xe3, 0x11, buf, sizeof(buf));


	if (rc < 0)
		return rc;


	au8522_rc_clear(ir, 0xe0, 1 << 4);


	au8522_rc_set(ir, 0xe0, 1 << 4);

	dprintk(16, "RC data received: %*ph\n", 40, buf);

	prv_bit = (buf[0] >> 7) & 0x01;
	width = 0;
	for (i = 0; i < sizeof(buf); i++) {
		for (j = 7; j >= 0; j--) {
			bit = (buf[i] >> j) & 0x01;
			if (bit == prv_bit) {
				width++;
				continue;
			}


			if (first) {
				first = false;

				init_ir_raw_event(&rawir);
				rawir.pulse = true;
				if (width > NEC_START_SPACE - 2 &&
				    width < NEC_START_SPACE + 2) {

					rawir.duration = NEC_START_PULSE;
					dprintk(16, "Storing NEC start %s with duration %d",
						rawir.pulse ? "pulse" : "space",
						rawir.duration);
				} else {

					rawir.duration = RC5_START_PULSE;
					dprintk(16, "Storing RC5 start %s with duration %d",
						rawir.pulse ? "pulse" : "space",
						rawir.duration);
				}
				ir_raw_event_store(ir->rc, &rawir);
			}

			init_ir_raw_event(&rawir);
			rawir.pulse = prv_bit ? false : true;
			rawir.duration = AU8522_UNIT * width;
			dprintk(16, "Storing %s with duration %d",
				rawir.pulse ? "pulse" : "space",
				rawir.duration);
			ir_raw_event_store(ir->rc, &rawir);

			width = 1;
			prv_bit = bit;
		}
	}

	init_ir_raw_event(&rawir);
	rawir.pulse = prv_bit ? false : true;
	rawir.duration = AU8522_UNIT * width;
	dprintk(16, "Storing end %s with duration %d",
		rawir.pulse ? "pulse" : "space",
		rawir.duration);
	ir_raw_event_store(ir->rc, &rawir);

	ir_raw_event_handle(ir->rc);

	return 1;
}

process_controller (Parser &parser, EventTwoBytes *tb)

{
	unsigned short cv;


	if (tb->controller_number <= 31) {


		cv = (unsigned short) controller_val[tb->controller_number];

		if (controller_14bit[tb->controller_number]) {
			cv = ((tb->value << 7) | (cv & 0x7f));
		} else {
			cv = tb->value;
		}

		controller_val[tb->controller_number] = (controller_value_t)cv;

	} else if ((tb->controller_number >= 32 &&
		    tb->controller_number <= 63)) {

		cv = (unsigned short) controller_val[tb->controller_number];


		int cn = tb->controller_number - 32;

		if (controller_14bit[cn] == false) {
			controller_14bit[cn] = true;
			cv = (cv << 7) | (tb->value & 0x7f);
		} else {
			cv = (cv & 0x3f80) | (tb->value & 0x7f);
		}

		controller_val[tb->controller_number] =
			(controller_value_t) cv;
	} else {


		controller_val[tb->controller_number] =
			(controller_value_t) tb->value;
	}


	if (tb->controller_number == 0) {
		bank_number = (unsigned short) controller_val[0];
		if (port.input()) {
			port.input()->bank_change (*port.input(), bank_number);
			port.input()->channel_bank_change[channel_number]
				(*port.input(), bank_number);
		}
	}

}

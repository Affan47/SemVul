rotate_rotor (int frontend_fd, int from_rotor_pos, int to_rotor_pos, int voltage_18, int hiband){


	float rotor_wait_time;
	int err=0;

	float speed_13V = 1.5;
	float speed_18V = 2.4;
	float degreesmoved,a1,a2;

	if (to_rotor_pos != 0) {
		if (from_rotor_pos != to_rotor_pos) {
			info("Moving rotor from position %i to position %i\n",from_rotor_pos,to_rotor_pos);
			if (from_rotor_pos == 0) {
				rotor_wait_time = 15;
			} else {
				a1 = rotor_angle(to_rotor_pos);
				a2 = rotor_angle(from_rotor_pos);
				degreesmoved = abs(a1-a2);
				if (degreesmoved>180) degreesmoved=360-degreesmoved;
				rotor_wait_time = degreesmoved / speed_18V;
			}


			if (err = ioctl(frontend_fd, FE_SET_TONE, SEC_TONE_OFF))
				return err;
			msleep(15);

			if (err = ioctl(frontend_fd, FE_SET_VOLTAGE, SEC_VOLTAGE_18))
				return err;
			msleep(15);
			err = rotor_command(frontend_fd, 9, to_rotor_pos, 0, 0);
			if (err) {
				info("Rotor move error!\n");
			} else {
				int i;
				info("Rotating");
				for (i=0; i<10; i++){
					usleep(rotor_wait_time*100000);
					info(".");
				}
				info("completed.\n");
			}

		} else {
			info("Rotor already at position %i\n", from_rotor_pos);
		}


		if (err = ioctl(frontend_fd, FE_SET_TONE, hiband ? SEC_TONE_ON : SEC_TONE_OFF))
                        return err;
		msleep(15);
		if (err = ioctl(frontend_fd, FE_SET_VOLTAGE, voltage_18))
			return err;
		msleep(15);
	}
	return err;
}

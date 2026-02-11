wait_keyup( void ) {

	while (1) {
		if ((get_key() & 0x80) != 0) {
			return;
		}


		if (serial_cons) {
			return;
		}
	}
}

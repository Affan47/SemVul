jack_transport_copy_position (jack_position_t *from, jack_position_t *to)
{
	int tries = 0;
	long timeout = 1000;

	do {


		if (tries > 10) {
			usleep (20);
			tries = 0;


			if (--timeout == 0) {
				jack_error ("hung in loop copying position B");
				abort();
			}
		}
		*to = *from;
		tries++;

	} while (to->unique_1 != to->unique_2);
}

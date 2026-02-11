set_step(float step)
{
	if ((step > 1.0) || (step < 0.0)) {
		step = 1.0;
	}

	pbar.set_fraction(step);
	flush_queue();
	usleep(SPLASH_SLEEP_USEC);
}

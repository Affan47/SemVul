jack_driver_nt_start (jack_driver_nt_t * driver)
{
	int err;


	pthread_mutex_lock (&driver->nt_run_lock);
	driver->nt_run = DRIVER_NT_RUN;

	if ((err = jack_client_create_thread (NULL,
					      &driver->nt_thread,
					      driver->engine->rtpriority,
					      driver->engine->control->real_time,
					      jack_driver_nt_thread, driver)) != 0) {
		jack_error ("DRIVER NT: could not start driver thread!");
		return err;
	}

	if ((err = driver->nt_start (driver)) != 0) {

		driver->nt_run = DRIVER_NT_EXIT;
		pthread_mutex_unlock (&driver->nt_run_lock);
		jack_error ("DRIVER NT: could not start driver");
		return err;
	}


	pthread_mutex_unlock (&driver->nt_run_lock);

	return 0;
}

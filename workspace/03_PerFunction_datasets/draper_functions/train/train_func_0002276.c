condvar_create(condvar_type_t type)
{
	switch (type)
	{
		case CONDVAR_TYPE_DEFAULT:
		default:
		{
			private_condvar_t *this;

			INIT(this,
				.public = {
					.wait = (void*)_wait_,
					.timed_wait = (void*)_timed_wait,
					.timed_wait_abs = (void*)_timed_wait_abs,
					.signal = _signal_,
					.broadcast = _broadcast,
					.destroy = _condvar_destroy,
				}
			);

#ifdef HAVE_PTHREAD_CONDATTR_INIT
			{
				pthread_condattr_t condattr;
				pthread_condattr_init(&condattr);
#ifdef HAVE_CONDATTR_CLOCK_MONOTONIC
				pthread_condattr_setclock(&condattr, CLOCK_MONOTONIC);
#endif
				pthread_cond_init(&this->condvar, &condattr);
				pthread_condattr_destroy(&condattr);
			}
#endif

			return &this->public;
		}
	}
}

run_once(void* arg)
{
#ifndef ENABLE_THREADS


  if (!this->was_run_)
    this->internal_run(arg);

#else

  if (parameters->options_valid() && !parameters->options().threads())
    {

      if (!this->was_run_)
	this->internal_run(arg);
      return;
    }


#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4
  while (true)
    {
      if (__sync_bool_compare_and_swap(&this->was_run_lock_, 0, 1))
	break;
    }
  bool was_run = this->was_run_;
  while (true)
    {
      if (__sync_bool_compare_and_swap(&this->was_run_lock_, 1, 0))
	break;
    }
  if (was_run)
    return;
#endif


  int err = pthread_mutex_lock(&once_pointer_control);
  if (err != 0)
    gold_fatal(_("pthread_mutex_lock failed: %s"), strerror(err));

  once_pointer = this;
  once_arg = arg;

  err = pthread_once(this->once_->once_control(), c_run_once);
  if (err != 0)
    gold_fatal(_("pthread_once failed: %s"), strerror(err));

  once_pointer = NULL;
  once_arg = NULL;

  err = pthread_mutex_unlock(&once_pointer_control);
  if (err != 0)
    gold_fatal(_("pthread_mutex_unlock failed: %s"), strerror(err));

#endif
}

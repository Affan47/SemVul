wait(Lock_impl* li)
{
  Lock_impl_threads* lit = static_cast<Lock_impl_threads*>(li);
  int err = pthread_cond_wait(&this->cond_, &lit->mutex_);
  if (err != 0)
    gold_fatal(_("pthread_cond_wait failed: %s"), strerror(err));
}

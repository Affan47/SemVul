thread_main(private_thread_t *this)
{
	void *res;

	sem_wait(&this->created);
	current_thread->set(current_thread, this);
	pthread_cleanup_push((thread_cleanup_t)thread_cleanup, this);


#ifdef HAVE_GETTID
	DBG2(DBG_LIB, "created thread %.2d [%u]",
		 this->id, gettid());
#elif defined(WIN32)
	DBG2(DBG_LIB, "created thread %.2d [%p]",
		 this->id, this->thread_id.p);
#else
	DBG2(DBG_LIB, "created thread %.2d [%lx]",
		 this->id, (u_long)this->thread_id);
#endif

	res = this->main(this->arg);
	pthread_cleanup_pop(TRUE);

	return res;
}

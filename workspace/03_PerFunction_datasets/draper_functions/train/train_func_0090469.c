interrupt(bool interruptSyscalls) {
	int ret;

	boost::thread::interrupt();
	if (interruptSyscalls && context->syscall_interruption_lock.try_lock()) {
		do {
			ret = pthread_kill(native_handle(),
				INTERRUPTION_SIGNAL);
		} while (ret == EINTR);
		context->syscall_interruption_lock.unlock();
	}
}

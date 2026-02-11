dispatch (int signum_)
{
	trace_with_mask("SigHandler::dispatch", SIGHAND);


	int my_errno = errno;

	EventHandler *eh = m_signal_handlers[signum_];

	if (eh != 0 && eh->handle_signal(signum_) == -1) {


		SigAction defact((C_SIG_HANDLER) SIG_DFL);
		m_signal_handlers[signum_] = 0;
		defact.register_action(signum_);
	}

	errno = my_errno;
}

dispatch (int signum_)
{
    trace_with_mask("SigHandlers::dispatch", SIGHAND);


    int errno_saved = errno;

    SigHandlersList& handlist = *(SigHandlersList::instance(signum_));
    SigHandlersList::iterator it;
    EventHandler* ehp;

    for (it=handlist.begin(); it != handlist.end(); it++) {
		ehp = *it;
		if (ehp->handle_signal (signum_) == -1) {


			handlist.erase (it);
		}
    }

    errno = errno_saved;
}

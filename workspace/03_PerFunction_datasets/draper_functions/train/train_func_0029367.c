Sleep(double seconds)
{
    Timespec start = Timespec::monotonic();
    SuspendFlags &s = SuspendFlags::getSuspendFlags();
    if (s.getState() == SuspendFlags::NORMAL) {
#ifdef HAVE_GLIB


        if (g_main_context_is_owner(g_main_context_default())) {
            bool triggered = false;
            GLibEvent timeout(g_timeout_add(seconds * 1000,
                                            SleepTimeout,
                                            &triggered),
                              "glib timeout");
            GRunWhile(! boost::lambda::var(triggered) &&
                      boost::lambda::bind(&SuspendFlags::getState, boost::ref(s)) == SuspendFlags::NORMAL);


            if (triggered) {
                timeout.release();
            }

            return 0;
        }
#endif


	Timespec deadline = start + Timespec(floor(seconds), (seconds - floor(seconds)) * 1e9);
	while (deadline > Timespec::monotonic()) {
            timeval delay;
            delay.tv_sec = 0;
            delay.tv_usec = 1e5;
            select(0, NULL, NULL, NULL, &delay);
            if (s.getState() != SuspendFlags::NORMAL) {
                break;
            }
        }
    }


    Timespec end = Timespec::monotonic();
    double left = (end - start).duration() - seconds;
    return std::max((double)0, left);
}

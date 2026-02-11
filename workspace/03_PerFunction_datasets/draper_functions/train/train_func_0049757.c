run_timer(Timer *timer)
{


    _lock.acquire_write();
    slim(click_jiffies());
    _lock.release_write();
    if (_timeout_j)
	timer->schedule_after_sec(_timeout_j / CLICK_HZ + 1);
}

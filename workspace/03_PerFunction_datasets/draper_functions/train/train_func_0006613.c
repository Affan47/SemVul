sal_sem_take(sal_sem_t b, int usec)
{
    sem_ctrl_t *s = (sem_ctrl_t *) b;
    int			err;

    if (usec == sal_sem_FOREVER && !in_interrupt()) {
	err = down_interruptible(&s->sem);
    } else {
	int		time_wait = 1;
        int             cnt = s->cnt;

	for (;;) {
	    if (down_trylock(&s->sem) == 0) {
		err = 0;
		break;
	    }

            if (s->binary) {


                if (time_wait > 1) {
                    err = 1;
                    break;
                }
                err = wait_event_interruptible_timeout(s->wq, cnt != s->cnt,
                                                       USEC_TO_JIFFIES(usec));
                if (err < 0) {
                    break;
                }
                time_wait++;

            } else {


                if (time_wait > usec) {
                    time_wait = usec;
                }

                sal_usleep(time_wait);

                usec -= time_wait;

                if (usec == 0) {
                    err = ETIMEDOUT;
                    break;
                }

                if ((time_wait *= 2) > 100000) {
                    time_wait = 100000;
                }
	    }
	}
    }
    return err ? -1 : 0;
}

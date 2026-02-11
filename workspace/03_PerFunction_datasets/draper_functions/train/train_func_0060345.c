get_ticket(stock)
    Ticket_Stock *stock;
{
    struct flock lock;
    int i;

    if (stock->file < 0)
	return -1;

    if (0 <= stock->lock_spot)
	return 0;


    for (i = 0; i < stock->count; i++) {
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = i;
        lock.l_len = 1;
        lock.l_pid = 0;
	if (fcntl(stock->file, F_SETLK, &lock) == 0) {
	    syslog(LOG_DEBUG, "debug: lock the spot %d on the lock file: %s",
		i, stock->file_name);
	    stock->lock_spot = i;
	    return 0;
	}
    }

    syslog(LOG_DEBUG, "debug: no free spot is left on the lock file: %s",
	stock->file_name);
    return -1;
}

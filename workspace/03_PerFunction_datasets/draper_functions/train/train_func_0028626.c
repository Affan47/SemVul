locking_slave(int in_fd, int out_fd)
{
    char cmd;
    int rv;
    file_lock *lock = file_lock_new(TEST_FILENAME);
    gboolean locked = 0;

    while (1) {
	if (!pipeget(in_fd, &cmd))
	    cmd = 'q';

	switch (cmd) {
	    case 'q':
		tu_dbg("slave: quitting\n");
		file_lock_free(lock);
		lock = NULL;
		return;

	    case 'l':
		g_assert(!locked);
		rv = file_lock_lock(lock);
		if (rv == -1) {
		    g_fprintf(stderr, "file_lock_lock: %s\n",
				    strerror(errno));
		    return;
		}
		tu_dbg("slave: lock attempt => %s\n", (rv == 1)? "n" : "y");
		pipeput(out_fd, (rv == 1)? "n" : "y");
		if (rv != 1)
		    locked = 1;
		break;

	    case 'i':
		g_assert(locked);
		if (!inc_counter(lock))
		    return;
		tu_dbg("slave: inc'd to %c\n", lock->data[0]);
		pipeput(out_fd, lock->data);
		break;

	    case 'u':
		g_assert(locked);
		rv = file_lock_unlock(lock);
		if (rv != 0) {
		    g_fprintf(stderr, "file_lock_unlock: %s\n",
			    strerror(errno));
		    return;
		}
		tu_dbg("slave: unlocked\n");
		pipeput(out_fd, "k");
		locked = 0;
		break;

	    default:
		return;
	}
    }
}

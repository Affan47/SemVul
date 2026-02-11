inc_counter(file_lock *lock)
{
    char old_val = 'a';
    char new_val;

    if (lock->len) {
	old_val = lock->data[0];
    }

    g_assert(old_val < 'z');

    new_val = old_val + 1;
    if (file_lock_write(lock, &new_val, 1) == -1) {
	g_fprintf(stderr, "file_lock_write: %s\n",
			strerror(errno));
	return FALSE;
    }

    return TRUE;
}

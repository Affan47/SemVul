kvv_time(RESULT * result, RESULT * arg1)
{
    int index = (int) R2N(arg1);
    double value = -1.0;

    kvv_start();

    if (kvv_fork() != 0) {
	SetResult(&result, R_STRING, "");
	return;
    }

    mutex_lock(mutex);

    if (index < shm->entries)
	value = shm->entry[index].time;

    SetResult(&result, R_NUMBER, &value);

    mutex_unlock(mutex);
}

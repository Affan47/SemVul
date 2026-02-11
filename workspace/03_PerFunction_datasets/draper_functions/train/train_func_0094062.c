rdu_lib_init(void)
{
	int err;

	err = 0;
	if (rdu)
		goto out;

	rdu_lib_lock();
	if (!rdu) {
		rdu = calloc(rdu_lim, sizeof(*rdu));
		err = !rdu;
	}
	rdu_lib_unlock();

 out:
	return err;
}

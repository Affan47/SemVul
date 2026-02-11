try_enter(cri_info_t *info) {
    cri_atomic_t *count = &info->cr_cs_count;
    int old;


    do {
	old = (int)cri_atomic_read(count);
    } while (!cri_cmp_swap(count, old, old + 1));

    if (old > 1) {

	cri_red_lock(&cri_cs_lock);
    } else if (cri_atomic_read(&cri_live_count) || cri_red_trylock(&cri_cs_lock)) {

#if 1


        sigset_t mask;
        sigemptyset(&mask);
        sigprocmask(SIG_UNBLOCK, &mask, NULL);
#endif
	poll_checkpoint(info);
	return 0;
    }


    return 1;
}

restart_thread(void __maybe_unused *arg)
{
	struct cgpu_info *cgpu;
	int i, mt;

	pthread_detach(pthread_self());


	discard_stale();

	rd_lock(&mining_thr_lock);
	mt = mining_threads;
	rd_unlock(&mining_thr_lock);

	for (i = 0; i < mt; i++) {
		cgpu = mining_thr[i]->cgpu;
		if (unlikely(!cgpu))
			continue;
		if (cgpu->deven != DEV_ENABLED)
			continue;
		mining_thr[i]->work_restart = true;
		flush_queue(cgpu);
		cgpu->drv->flush_work(cgpu);
	}

	mutex_lock(&restart_lock);
	pthread_cond_broadcast(&restart_cond);
	mutex_unlock(&restart_lock);

#ifdef USE_USBUTILS


	cancel_usb_transfers();
#endif
	return NULL;
}

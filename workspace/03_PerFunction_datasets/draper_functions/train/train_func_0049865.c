fill_queue(struct thr_info *mythr, struct cgpu_info *cgpu, struct device_drv *drv, const int thr_id)
{
	do {
		bool need_work;


		need_work = (!cgpu->unqueued_work);


		if (need_work) {
			struct work *work = get_work(mythr, thr_id);

			wr_lock(&cgpu->qlock);


			if (likely(!cgpu->unqueued_work))
				cgpu->unqueued_work = work;
			else
				need_work = false;
			wr_unlock(&cgpu->qlock);

			if (unlikely(!need_work))
				discard_work(work);
		}


	} while (!drv->queue_full(cgpu));
}

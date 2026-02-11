cpu_stop_queue_two_works(int cpu1, struct cpu_stop_work *work1,
				    int cpu2, struct cpu_stop_work *work2)
{
	struct cpu_stopper *stopper1 = per_cpu_ptr(&cpu_stopper, cpu1);
	struct cpu_stopper *stopper2 = per_cpu_ptr(&cpu_stopper, cpu2);
	int err;

	lg_double_lock(&stop_cpus_lock, cpu1, cpu2);
	spin_lock_irq(&stopper1->lock);
	spin_lock_nested(&stopper2->lock, SINGLE_DEPTH_NESTING);

	err = -ENOENT;
	if (!stopper1->enabled || !stopper2->enabled)
		goto unlock;

	err = 0;
	__cpu_stop_queue_work(stopper1, work1);
	__cpu_stop_queue_work(stopper2, work2);
unlock:
	spin_unlock(&stopper2->lock);
	spin_unlock_irq(&stopper1->lock);
	lg_double_unlock(&stop_cpus_lock, cpu1, cpu2);

	return err;
}

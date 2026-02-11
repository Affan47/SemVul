dispatch_job(struct kcopyd_job *job)
{
	struct dm_kcopyd_client *kc = job->kc;
	atomic_inc(&kc->nr_jobs);
	if (unlikely(!job->source.count))
		push(&kc->complete_jobs, job);
	else if (job->pages == &zero_page_list)
		push(&kc->io_jobs, job);
	else
		push(&kc->pages_jobs, job);
	wake(kc);
}

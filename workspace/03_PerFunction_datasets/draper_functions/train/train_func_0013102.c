kfd_process_notifier_release(struct mmu_notifier *mn,
					struct mm_struct *mm)
{
	struct kfd_process *p;
	struct kfd_process_device *pdd = NULL;


	p = container_of(mn, struct kfd_process, mmu_notifier);
	BUG_ON(p->mm != mm);

	mutex_lock(&kfd_processes_mutex);
	hash_del_rcu(&p->kfd_processes);
	mutex_unlock(&kfd_processes_mutex);
	synchronize_srcu(&kfd_processes_srcu);

	mutex_lock(&p->mutex);


	pqm_uninit(&p->pqm);


	list_for_each_entry(pdd, &p->per_device_data, per_device_list) {
		if ((pdd->dev->dbgmgr) &&
				(pdd->dev->dbgmgr->pasid == p->pasid))
			kfd_dbgmgr_destroy(pdd->dev->dbgmgr);

		if (pdd->reset_wavefronts) {
			pr_warn("amdkfd: Resetting all wave fronts\n");
			dbgdev_wave_reset_wavefronts(pdd->dev, p);
			pdd->reset_wavefronts = false;
		}
	}

	mutex_unlock(&p->mutex);


	atomic_inc(&p->mm->mm_count);
	mmu_notifier_unregister_no_release(&p->mmu_notifier, p->mm);
	mmu_notifier_call_srcu(&p->rcu, &kfd_process_destroy_delayed);
}

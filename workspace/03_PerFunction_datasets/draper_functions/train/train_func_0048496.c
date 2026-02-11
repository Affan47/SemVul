intel_mm_release(struct mmu_notifier *mn, struct mm_struct *mm)
{
	struct intel_svm *svm = container_of(mn, struct intel_svm, notifier);
	struct intel_svm_dev *sdev;


	svm->iommu->pasid_table[svm->pasid].val = 0;
	wmb();

	rcu_read_lock();
	list_for_each_entry_rcu(sdev, &svm->devs, list) {
		intel_flush_pasid_dev(svm, sdev, svm->pasid);
		intel_flush_svm_range_dev(svm, sdev, 0, -1, 0, !svm->mm);
	}
	rcu_read_unlock();

}

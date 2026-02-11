i915_mmu_notifier_create(struct mm_struct *mm)
{
	struct i915_mmu_notifier *mn;
	int ret;

	mn = kmalloc(sizeof(*mn), GFP_KERNEL);
	if (mn == NULL)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&mn->lock);
	mn->mn.ops = &i915_gem_userptr_notifier;
	mn->objects = RB_ROOT;
	mn->wq = alloc_workqueue("i915-userptr-release", WQ_UNBOUND, 0);
	if (mn->wq == NULL) {
		kfree(mn);
		return ERR_PTR(-ENOMEM);
	}


	ret = __mmu_notifier_register(&mn->mn, mm);
	if (ret) {
		destroy_workqueue(mn->wq);
		kfree(mn);
		return ERR_PTR(ret);
	}

	return mn;
}

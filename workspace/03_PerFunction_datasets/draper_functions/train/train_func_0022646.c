core_delete_hba(struct se_hba *hba)
{
	WARN_ON(hba->dev_count);

	hba->backend->ops->detach_hba(hba);

	spin_lock(&hba_lock);
	list_del(&hba->hba_node);
	spin_unlock(&hba_lock);

	pr_debug("CORE_HBA[%d] - Detached HBA from Generic Target"
			" Core\n", hba->hba_id);

	module_put(hba->backend->ops->owner);

	hba->backend = NULL;
	kfree(hba);
	return 0;
}

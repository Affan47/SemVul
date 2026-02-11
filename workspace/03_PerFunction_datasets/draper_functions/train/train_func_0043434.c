__fnic_set_state_flags(struct fnic *fnic, unsigned long st_flags,
			unsigned long clearbits)
{
	struct Scsi_Host *host = fnic->lport->host;
	int sh_locked = spin_is_locked(host->host_lock);
	unsigned long flags = 0;

	if (!sh_locked)
		spin_lock_irqsave(host->host_lock, flags);

	if (clearbits)
		fnic->state_flags &= ~st_flags;
	else
		fnic->state_flags |= st_flags;

	if (!sh_locked)
		spin_unlock_irqrestore(host->host_lock, flags);

	return;
}

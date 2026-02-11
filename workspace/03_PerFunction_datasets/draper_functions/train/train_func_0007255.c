sym53c8xx_timer(unsigned long npref)
{
	struct sym_hcb *np = (struct sym_hcb *)npref;
	unsigned long flags;

	spin_lock_irqsave(np->s.host->host_lock, flags);
	sym_timer(np);
	spin_unlock_irqrestore(np->s.host->host_lock, flags);
}

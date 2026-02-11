ath10k_pci_hif_stop(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	unsigned long flags;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot hif stop\n");


	ath10k_pci_safe_chip_reset(ar);

	ath10k_pci_irq_disable(ar);
	ath10k_pci_irq_sync(ar);
	ath10k_pci_flush(ar);

	spin_lock_irqsave(&ar_pci->ps_lock, flags);
	WARN_ON(ar_pci->ps_wake_refcount > 0);
	spin_unlock_irqrestore(&ar_pci->ps_lock, flags);
}

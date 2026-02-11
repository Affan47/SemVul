nes_free_qp_mem(struct nes_device *nesdev,
		struct nes_qp *nesqp, int virt_wqs)
{
	unsigned long flags;
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	if (!virt_wqs) {
		pci_free_consistent(nesdev->pcidev, nesqp->qp_mem_size,
				nesqp->hwqp.sq_vbase, nesqp->hwqp.sq_pbase);
	}else {
		spin_lock_irqsave(&nesadapter->pbl_lock, flags);
		nesadapter->free_256pbl++;
		spin_unlock_irqrestore(&nesadapter->pbl_lock, flags);
		pci_free_consistent(nesdev->pcidev, nesqp->qp_mem_size, nesqp->hwqp.q2_vbase, nesqp->hwqp.q2_pbase);
		pci_free_consistent(nesdev->pcidev, 256, nesqp->pbl_vbase, nesqp->pbl_pbase );
		nesqp->pbl_vbase = NULL;
		if (nesqp->sq_kmapped) {
			nesqp->sq_kmapped = 0;
			kunmap(nesqp->page);
		}
	}
}

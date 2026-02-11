usnic_fwd_alloc_flow(struct usnic_fwd_dev *ufdev, struct filter *filter,
				struct usnic_filter_action *uaction)
{
	struct filter_tlv *tlv;
	struct pci_dev *pdev;
	struct usnic_fwd_flow *flow;
	uint64_t a0, a1;
	uint64_t tlv_size;
	dma_addr_t tlv_pa;
	int status;

	pdev = ufdev->pdev;
	tlv_size = (2*sizeof(struct filter_tlv) + sizeof(struct filter) +
			sizeof(struct filter_action));

	flow = kzalloc(sizeof(*flow), GFP_ATOMIC);
	if (!flow)
		return ERR_PTR(-ENOMEM);

	tlv = pci_alloc_consistent(pdev, tlv_size, &tlv_pa);
	if (!tlv) {
		usnic_err("Failed to allocate memory\n");
		status = -ENOMEM;
		goto out_free_flow;
	}

	fill_tlv(tlv, filter, &uaction->action);

	spin_lock(&ufdev->lock);
	status = usnic_fwd_dev_ready_locked(ufdev);
	if (status) {
		usnic_err("Forwarding dev %s not ready with status %d\n",
				ufdev->name, status);
		goto out_free_tlv;
	}

	status = validate_filter_locked(ufdev, filter);
	if (status) {
		usnic_err("Failed to validate filter with status %d\n",
				status);
		goto out_free_tlv;
	}


	a0 = tlv_pa;
	a1 = tlv_size;
	status = usnic_fwd_devcmd_locked(ufdev, uaction->vnic_idx,
						CMD_ADD_FILTER, &a0, &a1);
	if (status) {
		usnic_err("VF %s Filter add failed with status:%d",
				ufdev->name, status);
		status = -EFAULT;
		goto out_free_tlv;
	} else {
		usnic_dbg("VF %s FILTER ID:%llu", ufdev->name, a0);
	}

	flow->flow_id = (uint32_t) a0;
	flow->vnic_idx = uaction->vnic_idx;
	flow->ufdev = ufdev;

out_free_tlv:
	spin_unlock(&ufdev->lock);
	pci_free_consistent(pdev, tlv_size, tlv, tlv_pa);
	if (!status)
		return flow;
out_free_flow:
	kfree(flow);
	return ERR_PTR(status);
}

new_pcichild_device(struct hv_pcibus_device *hbus,
		struct pci_function_description *desc)
{
	struct hv_pci_dev *hpdev;
	struct pci_child_message *res_req;
	struct q_res_req_compl comp_pkt;
	union {
	struct pci_packet init_packet;
		u8 buffer[0x100];
	} pkt;
	unsigned long flags;
	int ret;

	hpdev = kzalloc(sizeof(*hpdev), GFP_ATOMIC);
	if (!hpdev)
		return NULL;

	hpdev->hbus = hbus;

	memset(&pkt, 0, sizeof(pkt));
	init_completion(&comp_pkt.host_event);
	comp_pkt.hpdev = hpdev;
	pkt.init_packet.compl_ctxt = &comp_pkt;
	pkt.init_packet.completion_func = q_resource_requirements;
	res_req = (struct pci_child_message *)&pkt.init_packet.message;
	res_req->message_type.type = PCI_QUERY_RESOURCE_REQUIREMENTS;
	res_req->wslot.slot = desc->win_slot.slot;

	ret = vmbus_sendpacket(hbus->hdev->channel, res_req,
			       sizeof(struct pci_child_message),
			       (unsigned long)&pkt.init_packet,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	if (ret)
		goto error;

	wait_for_completion(&comp_pkt.host_event);

	hpdev->desc = *desc;
	get_pcichild(hpdev, hv_pcidev_ref_initial);
	get_pcichild(hpdev, hv_pcidev_ref_childlist);
	spin_lock_irqsave(&hbus->device_list_lock, flags);


	if (list_empty(&hbus->children))
		hbus->sysdata.domain = desc->ser & 0xFFFF;
	list_add_tail(&hpdev->list_entry, &hbus->children);
	spin_unlock_irqrestore(&hbus->device_list_lock, flags);
	return hpdev;

error:
	kfree(hpdev);
	return NULL;
}

btusb_setup_intel_patching(struct hci_dev *hdev,
				      const struct firmware *fw,
				      const u8 **fw_ptr, int *disable_patch)
{
	struct sk_buff *skb;
	struct hci_command_hdr *cmd;
	const u8 *cmd_param;
	struct hci_event_hdr *evt = NULL;
	const u8 *evt_param = NULL;
	int remain = fw->size - (*fw_ptr - fw->data);


	if (remain > HCI_COMMAND_HDR_SIZE && *fw_ptr[0] != 0x01) {
		BT_ERR("%s Intel fw corrupted: invalid cmd read", hdev->name);
		return -EINVAL;
	}
	(*fw_ptr)++;
	remain--;

	cmd = (struct hci_command_hdr *)(*fw_ptr);
	*fw_ptr += sizeof(*cmd);
	remain -= sizeof(*cmd);


	if (remain < cmd->plen) {
		BT_ERR("%s Intel fw corrupted: invalid cmd len", hdev->name);
		return -EFAULT;
	}


	if (*disable_patch && le16_to_cpu(cmd->opcode) == 0xfc8e)
		*disable_patch = 0;

	cmd_param = *fw_ptr;
	*fw_ptr += cmd->plen;
	remain -= cmd->plen;


	while (remain > HCI_EVENT_HDR_SIZE && *fw_ptr[0] == 0x02) {
		(*fw_ptr)++;
		remain--;

		evt = (struct hci_event_hdr *)(*fw_ptr);
		*fw_ptr += sizeof(*evt);
		remain -= sizeof(*evt);

		if (remain < evt->plen) {
			BT_ERR("%s Intel fw corrupted: invalid evt len",
			       hdev->name);
			return -EFAULT;
		}

		evt_param = *fw_ptr;
		*fw_ptr += evt->plen;
		remain -= evt->plen;
	}


	if (!evt || !evt_param || remain < 0) {
		BT_ERR("%s Intel fw corrupted: invalid evt read", hdev->name);
		return -EFAULT;
	}

	skb = __hci_cmd_sync_ev(hdev, le16_to_cpu(cmd->opcode), cmd->plen,
				cmd_param, evt->evt, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		BT_ERR("%s sending Intel patch command (0x%4.4x) failed (%ld)",
		       hdev->name, cmd->opcode, PTR_ERR(skb));
		return PTR_ERR(skb);
	}


	if (skb->len != evt->plen) {
		BT_ERR("%s mismatch event length (opcode 0x%4.4x)", hdev->name,
		       le16_to_cpu(cmd->opcode));
		kfree_skb(skb);
		return -EFAULT;
	}

	if (memcmp(skb->data, evt_param, evt->plen)) {
		BT_ERR("%s mismatch event parameter (opcode 0x%4.4x)",
		       hdev->name, le16_to_cpu(cmd->opcode));
		kfree_skb(skb);
		return -EFAULT;
	}
	kfree_skb(skb);

	return 0;
}

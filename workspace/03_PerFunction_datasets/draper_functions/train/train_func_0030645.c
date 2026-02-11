ibft_create_kobject(struct acpi_table_ibft *header,
				      struct ibft_hdr *hdr)
{
	struct iscsi_boot_kobj *boot_kobj = NULL;
	struct ibft_kobject *ibft_kobj = NULL;
	struct ibft_nic *nic = (struct ibft_nic *)hdr;
	struct pci_dev *pci_dev;
	int rc = 0;

	ibft_kobj = kzalloc(sizeof(*ibft_kobj), GFP_KERNEL);
	if (!ibft_kobj)
		return -ENOMEM;

	ibft_kobj->header = header;
	ibft_kobj->hdr = hdr;

	switch (hdr->id) {
	case id_initiator:
		rc = ibft_verify_hdr("initiator", hdr, id_initiator,
				     sizeof(*ibft_kobj->initiator));
		if (rc)
			break;

		boot_kobj = iscsi_boot_create_initiator(boot_kset, hdr->index,
						ibft_kobj,
						ibft_attr_show_initiator,
						ibft_check_initiator_for,
						ibft_kobj_release);
		if (!boot_kobj) {
			rc = -ENOMEM;
			goto free_ibft_obj;
		}
		break;
	case id_nic:
		rc = ibft_verify_hdr("ethernet", hdr, id_nic,
				     sizeof(*ibft_kobj->nic));
		if (rc)
			break;

		boot_kobj = iscsi_boot_create_ethernet(boot_kset, hdr->index,
						       ibft_kobj,
						       ibft_attr_show_nic,
						       ibft_check_nic_for,
						       ibft_kobj_release);
		if (!boot_kobj) {
			rc = -ENOMEM;
			goto free_ibft_obj;
		}
		break;
	case id_target:
		rc = ibft_verify_hdr("target", hdr, id_target,
				     sizeof(*ibft_kobj->tgt));
		if (rc)
			break;

		boot_kobj = iscsi_boot_create_target(boot_kset, hdr->index,
						     ibft_kobj,
						     ibft_attr_show_target,
						     ibft_check_tgt_for,
						     ibft_kobj_release);
		if (!boot_kobj) {
			rc = -ENOMEM;
			goto free_ibft_obj;
		}
		break;
	case id_reserved:
	case id_control:
	case id_extensions:

		rc = 1;
		break;
	default:
		printk(KERN_ERR "iBFT has unknown structure type (%d). " \
				"Report this bug to %.6s!\n", hdr->id,
				header->header.oem_id);
		rc = 1;
		break;
	}

	if (rc) {

		rc = 0;
		goto free_ibft_obj;
	}

	if (hdr->id == id_nic) {


		pci_dev = pci_get_bus_and_slot((nic->pci_bdf & 0xff00) >> 8,
					       (nic->pci_bdf & 0xff));
		if (pci_dev) {
			rc = sysfs_create_link(&boot_kobj->kobj,
					       &pci_dev->dev.kobj, "device");
			pci_dev_put(pci_dev);
		}
	}
	return 0;

free_ibft_obj:
	kfree(ibft_kobj);
	return rc;
}

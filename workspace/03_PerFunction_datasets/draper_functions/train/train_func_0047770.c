put_pcichild(struct hv_pci_dev *hpdev,
			    enum hv_pcidev_ref_reason reason)
{
	if (atomic_dec_and_test(&hpdev->refs))
		kfree(hpdev);
}

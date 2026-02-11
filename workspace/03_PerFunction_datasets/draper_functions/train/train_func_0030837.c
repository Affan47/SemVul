vga_arb_read(struct file *file, char __user *buf,
			    size_t count, loff_t *ppos)
{
	struct vga_arb_private *priv = file->private_data;
	struct vga_device *vgadev;
	struct pci_dev *pdev;
	unsigned long flags;
	size_t len;
	int rc;
	char *lbuf;

	lbuf = kmalloc(1024, GFP_KERNEL);
	if (lbuf == NULL)
		return -ENOMEM;


	spin_lock_irqsave(&vga_lock, flags);


	pdev = priv->target;
	if (pdev == NULL || pdev == PCI_INVALID_CARD) {
		spin_unlock_irqrestore(&vga_lock, flags);
		len = sprintf(lbuf, "invalid");
		goto done;
	}


	vgadev = vgadev_find(pdev);
	if (vgadev == NULL) {


		if (pdev == priv->target)
			vga_arb_device_card_gone(pdev);
		spin_unlock_irqrestore(&vga_lock, flags);
		len = sprintf(lbuf, "invalid");
		goto done;
	}


	len = snprintf(lbuf, 1024,
		       "count:%d,PCI:%s,decodes=%s,owns=%s,locks=%s(%d:%d)\n",
		       vga_decode_count, pci_name(pdev),
		       vga_iostate_to_str(vgadev->decodes),
		       vga_iostate_to_str(vgadev->owns),
		       vga_iostate_to_str(vgadev->locks),
		       vgadev->io_lock_cnt, vgadev->mem_lock_cnt);

	spin_unlock_irqrestore(&vga_lock, flags);
done:


	if (len > count)
		len = count;
	rc = copy_to_user(buf, lbuf, len);
	kfree(lbuf);
	if (rc)
		return -EFAULT;
	return len;
}

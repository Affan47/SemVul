vga_client_register(struct pci_dev *pdev, void *cookie,
			void (*irq_set_state)(void *cookie, bool state),
			unsigned int (*set_vga_decode)(void *cookie,
						       bool decode))
{
	int ret = -ENODEV;
	struct vga_device *vgadev;
	unsigned long flags;

	spin_lock_irqsave(&vga_lock, flags);
	vgadev = vgadev_find(pdev);
	if (!vgadev)
		goto bail;

	vgadev->irq_set_state = irq_set_state;
	vgadev->set_vga_decode = set_vga_decode;
	vgadev->cookie = cookie;
	ret = 0;

bail:
	spin_unlock_irqrestore(&vga_lock, flags);
	return ret;

}

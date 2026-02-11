udl_free_urb_list(struct drm_device *dev)
{
	struct udl_device *udl = dev->dev_private;
	int count = udl->urbs.count;
	struct list_head *node;
	struct urb_node *unode;
	struct urb *urb;
	int ret;
	unsigned long flags;

	DRM_DEBUG("Waiting for completes and freeing all render urbs\n");


	while (count--) {


		ret = down_interruptible(&udl->urbs.limit_sem);
		if (ret)
			break;

		spin_lock_irqsave(&udl->urbs.lock, flags);

		node = udl->urbs.list.next;
		list_del_init(node);

		spin_unlock_irqrestore(&udl->urbs.lock, flags);

		unode = list_entry(node, struct urb_node, entry);
		urb = unode->urb;


		usb_free_coherent(urb->dev, udl->urbs.size,
				  urb->transfer_buffer, urb->transfer_dma);
		usb_free_urb(urb);
		kfree(node);
	}
	udl->urbs.count = 0;
}

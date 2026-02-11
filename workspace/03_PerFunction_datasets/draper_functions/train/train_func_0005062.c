usb_add_gadget_udc_release(struct device *parent, struct usb_gadget *gadget,
		void (*release)(struct device *dev))
{
	struct usb_udc		*udc;
	int			ret = -ENOMEM;

	udc = kzalloc(sizeof(*udc), GFP_KERNEL);
	if (!udc)
		goto err1;

	dev_set_name(&gadget->dev, "gadget");
	INIT_WORK(&gadget->work, usb_gadget_state_work);
	gadget->dev.parent = parent;

#ifdef	CONFIG_HAS_DMA
	dma_set_coherent_mask(&gadget->dev, parent->coherent_dma_mask);
	gadget->dev.dma_parms = parent->dma_parms;
	gadget->dev.dma_mask = parent->dma_mask;
#endif

	if (release)
		gadget->dev.release = release;
	else
		gadget->dev.release = usb_udc_nop_release;

	ret = device_register(&gadget->dev);
	if (ret)
		goto err2;

	device_initialize(&udc->dev);
	udc->dev.release = usb_udc_release;
	udc->dev.class = udc_class;
	udc->dev.groups = usb_udc_attr_groups;
	udc->dev.parent = parent;
	ret = dev_set_name(&udc->dev, "%s", kobject_name(&parent->kobj));
	if (ret)
		goto err3;

	udc->gadget = gadget;
	gadget->udc = udc;

	mutex_lock(&udc_lock);
	list_add_tail(&udc->list, &udc_list);

	ret = device_add(&udc->dev);
	if (ret)
		goto err4;

	usb_gadget_set_state(gadget, USB_STATE_NOTATTACHED);
	udc->vbus = true;

	mutex_unlock(&udc_lock);

	return 0;

err4:
	list_del(&udc->list);
	mutex_unlock(&udc_lock);

err3:
	put_device(&udc->dev);
	device_del(&gadget->dev);

err2:
	put_device(&gadget->dev);
	kfree(udc);

err1:
	return ret;
}

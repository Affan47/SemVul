vme_master_free(struct vme_resource *resource)
{
	struct vme_master_resource *master_image;

	if (resource->type != VME_MASTER) {
		printk(KERN_ERR "Not a master resource\n");
		return;
	}

	master_image = list_entry(resource->entry, struct vme_master_resource,
		list);
	if (master_image == NULL) {
		printk(KERN_ERR "Can't find master resource\n");
		return;
	}


	spin_lock(&master_image->lock);
	if (master_image->locked == 0)
		printk(KERN_ERR "Image is already free\n");

	master_image->locked = 0;
	spin_unlock(&master_image->lock);


	kfree(resource);
}

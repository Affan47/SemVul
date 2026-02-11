vme_lm_count(struct vme_resource *resource)
{
	struct vme_lm_resource *lm;

	if (resource->type != VME_LM) {
		printk(KERN_ERR "Not a Location Monitor resource\n");
		return -EINVAL;
	}

	lm = list_entry(resource->entry, struct vme_lm_resource, list);

	return lm->monitors;
}

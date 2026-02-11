rio_get_comptag(u32 comp_tag, struct rio_dev *from)
{
	struct list_head *n;
	struct rio_dev *rdev;

	spin_lock(&rio_global_list_lock);
	n = from ? from->global_list.next : rio_devices.next;

	while (n && (n != &rio_devices)) {
		rdev = rio_dev_g(n);
		if (rdev->comp_tag == comp_tag)
			goto exit;
		n = n->next;
	}
	rdev = NULL;
exit:
	spin_unlock(&rio_global_list_lock);
	return rdev;
}

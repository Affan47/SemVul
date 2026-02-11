rbd_dev_parent_put(struct rbd_device *rbd_dev)
{
	int counter;

	if (!rbd_dev->parent_spec)
		return;

	counter = atomic_dec_return_safe(&rbd_dev->parent_ref);
	if (counter > 0)
		return;


	if (!counter)
		rbd_dev_unparent(rbd_dev);
	else
		rbd_warn(rbd_dev, "parent reference underflow");
}

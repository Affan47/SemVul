vfio_group_schedule_put(struct vfio_group *group)
{
	struct vfio_group_put_work *do_work;

	do_work = kmalloc(sizeof(*do_work), GFP_KERNEL);
	if (WARN_ON(!do_work))
		return;

	INIT_WORK(&do_work->work, vfio_group_put_bg);
	do_work->group = group;
	schedule_work(&do_work->work);
}

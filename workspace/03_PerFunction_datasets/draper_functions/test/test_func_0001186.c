iio_sysfs_trigger_probe(int id)
{
	struct iio_sysfs_trig *t;
	int ret;
	bool foundit = false;

	mutex_lock(&iio_sysfs_trig_list_mut);
	list_for_each_entry(t, &iio_sysfs_trig_list, l)
		if (id == t->id) {
			foundit = true;
			break;
		}
	if (foundit) {
		ret = -EINVAL;
		goto out1;
	}
	t = kmalloc(sizeof(*t), GFP_KERNEL);
	if (t == NULL) {
		ret = -ENOMEM;
		goto out1;
	}
	t->id = id;
	t->trig = iio_trigger_alloc("sysfstrig%d", id);
	if (!t->trig) {
		ret = -ENOMEM;
		goto free_t;
	}

	t->trig->dev.groups = iio_sysfs_trigger_attr_groups;
	t->trig->ops = &iio_sysfs_trigger_ops;
	t->trig->dev.parent = &iio_sysfs_trig_dev;
	iio_trigger_set_drvdata(t->trig, t);

	init_irq_work(&t->work, iio_sysfs_trigger_work);

	ret = iio_trigger_register(t->trig);
	if (ret)
		goto out2;
	list_add(&t->l, &iio_sysfs_trig_list);
	__module_get(THIS_MODULE);
	mutex_unlock(&iio_sysfs_trig_list_mut);
	return 0;

out2:
	iio_trigger_free(t->trig);
free_t:
	kfree(t);
out1:
	mutex_unlock(&iio_sysfs_trig_list_mut);
	return ret;
}

hfi1_qp_init(struct hfi1_ibdev *dev)
{
	struct hfi1_devdata *dd = dd_from_dev(dev);
	int i;
	int ret = -ENOMEM;


	dev->qp_dev = kzalloc(sizeof(*dev->qp_dev), GFP_KERNEL);
	if (!dev->qp_dev)
		goto nomem;

	dev->qp_dev->qp_table_size = hfi1_qp_table_size;
	dev->qp_dev->qp_table_bits = ilog2(hfi1_qp_table_size);
	dev->qp_dev->qp_table =
		kmalloc(dev->qp_dev->qp_table_size *
				sizeof(*dev->qp_dev->qp_table),
			GFP_KERNEL);
	if (!dev->qp_dev->qp_table)
		goto nomem;
	for (i = 0; i < dev->qp_dev->qp_table_size; i++)
		RCU_INIT_POINTER(dev->qp_dev->qp_table[i], NULL);
	spin_lock_init(&dev->qp_dev->qpt_lock);

	ret = init_qpn_table(dd, &dev->qp_dev->qpn_table);
	if (ret)
		goto nomem;
	return ret;
nomem:
	if (dev->qp_dev) {
		kfree(dev->qp_dev->qp_table);
		free_qpn_table(&dev->qp_dev->qpn_table);
		kfree(dev->qp_dev);
	}
	return ret;
}

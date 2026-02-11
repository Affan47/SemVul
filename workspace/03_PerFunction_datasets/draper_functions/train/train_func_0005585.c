nvdimm_probe(struct device *dev)
{
	struct nvdimm_drvdata *ndd;
	int rc;

	ndd = kzalloc(sizeof(*ndd), GFP_KERNEL);
	if (!ndd)
		return -ENOMEM;

	dev_set_drvdata(dev, ndd);
	ndd->dpa.name = dev_name(dev);
	ndd->ns_current = -1;
	ndd->ns_next = -1;
	ndd->dpa.start = 0;
	ndd->dpa.end = -1;
	ndd->dev = dev;
	get_device(dev);
	kref_init(&ndd->kref);

	rc = nvdimm_init_nsarea(ndd);
	if (rc)
		goto err;

	rc = nvdimm_init_config_data(ndd);
	if (rc)
		goto err;

	dev_dbg(dev, "config data size: %d\n", ndd->nsarea.config_size);

	nvdimm_bus_lock(dev);
	ndd->ns_current = nd_label_validate(ndd);
	ndd->ns_next = nd_label_next_nsindex(ndd->ns_current);
	nd_label_copy(ndd, to_next_namespace_index(ndd),
			to_current_namespace_index(ndd));
	rc = nd_label_reserve_dpa(ndd);
	nvdimm_bus_unlock(dev);

	if (rc)
		goto err;

	return 0;

 err:
	put_ndd(ndd);
	return rc;
}

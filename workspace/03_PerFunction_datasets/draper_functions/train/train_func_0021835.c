vp_request_msix_vectors(struct virtio_device *vdev, int nvectors,
				   bool per_vq_vectors)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);
	const char *name = dev_name(&vp_dev->vdev.dev);
	unsigned i, v;
	int err = -ENOMEM;

	vp_dev->msix_vectors = nvectors;

	vp_dev->msix_entries = kmalloc(nvectors * sizeof *vp_dev->msix_entries,
				       GFP_KERNEL);
	if (!vp_dev->msix_entries)
		goto error;
	vp_dev->msix_names = kmalloc(nvectors * sizeof *vp_dev->msix_names,
				     GFP_KERNEL);
	if (!vp_dev->msix_names)
		goto error;
	vp_dev->msix_affinity_masks
		= kzalloc(nvectors * sizeof *vp_dev->msix_affinity_masks,
			  GFP_KERNEL);
	if (!vp_dev->msix_affinity_masks)
		goto error;
	for (i = 0; i < nvectors; ++i)
		if (!alloc_cpumask_var(&vp_dev->msix_affinity_masks[i],
					GFP_KERNEL))
			goto error;

	for (i = 0; i < nvectors; ++i)
		vp_dev->msix_entries[i].entry = i;

	err = pci_enable_msix_exact(vp_dev->pci_dev,
				    vp_dev->msix_entries, nvectors);
	if (err)
		goto error;
	vp_dev->msix_enabled = 1;


	v = vp_dev->msix_used_vectors;
	snprintf(vp_dev->msix_names[v], sizeof *vp_dev->msix_names,
		 "%s-config", name);
	err = request_irq(vp_dev->msix_entries[v].vector,
			  vp_config_changed, 0, vp_dev->msix_names[v],
			  vp_dev);
	if (err)
		goto error;
	++vp_dev->msix_used_vectors;

	v = vp_dev->config_vector(vp_dev, v);

	if (v == VIRTIO_MSI_NO_VECTOR) {
		err = -EBUSY;
		goto error;
	}

	if (!per_vq_vectors) {

		v = vp_dev->msix_used_vectors;
		snprintf(vp_dev->msix_names[v], sizeof *vp_dev->msix_names,
			 "%s-virtqueues", name);
		err = request_irq(vp_dev->msix_entries[v].vector,
				  vp_vring_interrupt, 0, vp_dev->msix_names[v],
				  vp_dev);
		if (err)
			goto error;
		++vp_dev->msix_used_vectors;
	}
	return 0;
error:
	vp_free_vectors(vdev);
	return err;
}

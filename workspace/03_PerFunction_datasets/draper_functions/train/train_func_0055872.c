vp_set_vq_affinity(struct virtqueue *vq, int cpu)
{
	struct virtio_device *vdev = vq->vdev;
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);
	struct virtio_pci_vq_info *info = vp_dev->vqs[vq->index];
	struct cpumask *mask;
	unsigned int irq;

	if (!vq->callback)
		return -EINVAL;

	if (vp_dev->msix_enabled) {
		mask = vp_dev->msix_affinity_masks[info->msix_vector];
		irq = vp_dev->msix_entries[info->msix_vector].vector;
		if (cpu == -1)
			irq_set_affinity_hint(irq, NULL);
		else {
			cpumask_clear(mask);
			cpumask_set_cpu(cpu, mask);
			irq_set_affinity_hint(irq, mask);
		}
	}
	return 0;
}

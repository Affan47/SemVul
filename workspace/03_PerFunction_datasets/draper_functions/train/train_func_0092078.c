vm_del_vq(struct virtqueue *vq)
{
	struct virtio_mmio_device *vm_dev = to_virtio_mmio_device(vq->vdev);
	struct virtio_mmio_vq_info *info = vq->priv;
	unsigned long flags, size;
	unsigned int index = vq->index;

	spin_lock_irqsave(&vm_dev->lock, flags);
	list_del(&info->node);
	spin_unlock_irqrestore(&vm_dev->lock, flags);

	vring_del_virtqueue(vq);


	writel(index, vm_dev->base + VIRTIO_MMIO_QUEUE_SEL);
	if (vm_dev->version == 1) {
		writel(0, vm_dev->base + VIRTIO_MMIO_QUEUE_PFN);
	} else {
		writel(0, vm_dev->base + VIRTIO_MMIO_QUEUE_READY);
		WARN_ON(readl(vm_dev->base + VIRTIO_MMIO_QUEUE_READY));
	}

	size = PAGE_ALIGN(vring_size(info->num, VIRTIO_MMIO_VRING_ALIGN));
	free_pages_exact(info->queue, size);
	kfree(info);
}

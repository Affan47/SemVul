detach_buf(struct vring_virtqueue *vq, unsigned int head)
{
	unsigned int i;


	vq->data[head] = NULL;


	i = head;


	if (vq->vring.desc[i].flags & cpu_to_virtio16(vq->vq.vdev, VRING_DESC_F_INDIRECT))
		kfree(phys_to_virt(virtio64_to_cpu(vq->vq.vdev, vq->vring.desc[i].addr)));

	while (vq->vring.desc[i].flags & cpu_to_virtio16(vq->vq.vdev, VRING_DESC_F_NEXT)) {
		i = virtio16_to_cpu(vq->vq.vdev, vq->vring.desc[i].next);
		vq->vq.num_free++;
	}

	vq->vring.desc[i].next = cpu_to_virtio16(vq->vq.vdev, vq->free_head);
	vq->free_head = head;

	vq->vq.num_free++;
}

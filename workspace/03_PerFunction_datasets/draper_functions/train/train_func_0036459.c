videobuf_vm_close(struct vm_area_struct *vma)
{
	struct videobuf_mapping *map = vma->vm_private_data;
	struct videobuf_queue *q = map->q;
	struct videobuf_dma_sg_memory *mem;
	int i;

	dprintk(2, "vm_close %p [count=%d,vma=%08lx-%08lx]\n", map,
		map->count, vma->vm_start, vma->vm_end);

	map->count--;
	if (0 == map->count) {
		dprintk(1, "munmap %p q=%p\n", map, q);
		videobuf_queue_lock(q);
		for (i = 0; i < VIDEO_MAX_FRAME; i++) {
			if (NULL == q->bufs[i])
				continue;
			mem = q->bufs[i]->priv;
			if (!mem)
				continue;

			MAGIC_CHECK(mem->magic, MAGIC_SG_MEM);

			if (q->bufs[i]->map != map)
				continue;
			q->bufs[i]->map   = NULL;
			q->bufs[i]->baddr = 0;
			q->ops->buf_release(q, q->bufs[i]);
		}
		videobuf_queue_unlock(q);
		kfree(map);
	}
	return;
}

rt2x00debug_read_queue_stats(struct file *file,
					    char __user *buf,
					    size_t length,
					    loff_t *offset)
{
	struct rt2x00debug_intf *intf = file->private_data;
	struct data_queue *queue;
	unsigned long irqflags;
	unsigned int lines = 1 + intf->rt2x00dev->data_queues;
	size_t size;
	char *data;
	char *temp;

	if (*offset)
		return 0;

	data = kcalloc(lines, MAX_LINE_LENGTH, GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	temp = data +
	    sprintf(data, "qid\tflags\t\tcount\tlimit\tlength\tindex\tdma done\tdone\n");

	queue_for_each(intf->rt2x00dev, queue) {
		spin_lock_irqsave(&queue->index_lock, irqflags);

		temp += sprintf(temp, "%d\t0x%.8x\t%d\t%d\t%d\t%d\t%d\t\t%d\n",
				queue->qid, (unsigned int)queue->flags,
				queue->count, queue->limit, queue->length,
				queue->index[Q_INDEX],
				queue->index[Q_INDEX_DMA_DONE],
				queue->index[Q_INDEX_DONE]);

		spin_unlock_irqrestore(&queue->index_lock, irqflags);
	}

	size = strlen(data);
	size = min(size, length);

	if (copy_to_user(buf, data, size)) {
		kfree(data);
		return -EFAULT;
	}

	kfree(data);

	*offset += size;
	return size;
}

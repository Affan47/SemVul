tomoyo_read_log(struct tomoyo_io_buffer *head)
{
	struct tomoyo_log *ptr = NULL;
	if (head->r.w_pos)
		return;
	kfree(head->read_buf);
	head->read_buf = NULL;
	spin_lock(&tomoyo_log_lock);
	if (!list_empty(&tomoyo_log)) {
		ptr = list_entry(tomoyo_log.next, typeof(*ptr), list);
		list_del(&ptr->list);
		tomoyo_log_count--;
		tomoyo_memory_used[TOMOYO_MEMORY_AUDIT] -= ptr->size;
	}
	spin_unlock(&tomoyo_log_lock);
	if (ptr) {
		head->read_buf = ptr->log;
		head->r.w[head->r.w_pos++] = head->read_buf;
		kfree(ptr);
	}
}

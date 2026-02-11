n_hdlc_buf_return(struct n_hdlc_buf_list *buf_list,
						struct n_hdlc_buf *buf)
{
	unsigned long flags;

	spin_lock_irqsave(&buf_list->spinlock, flags);

	list_add(&buf->list_item, &buf_list->list);
	buf_list->count++;

	spin_unlock_irqrestore(&buf_list->spinlock, flags);
}

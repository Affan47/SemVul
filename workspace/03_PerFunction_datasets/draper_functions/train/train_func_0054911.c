xpc_free_msg_slot_uv(struct xpc_channel *ch,
		     struct xpc_send_msg_slot_uv *msg_slot)
{
	xpc_put_fifo_entry_uv(&ch->sn.uv.msg_slot_free_list, &msg_slot->next);


	if (atomic_read(&ch->n_on_msg_allocate_wq) > 0)
		wake_up(&ch->msg_allocate_wq);
}

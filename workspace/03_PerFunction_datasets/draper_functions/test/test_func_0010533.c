xpc_notify_senders_of_disconnect_uv(struct xpc_channel *ch)
{
	struct xpc_send_msg_slot_uv *msg_slot;
	int entry;

	DBUG_ON(!(ch->flags & XPC_C_DISCONNECTING));

	for (entry = 0; entry < ch->local_nentries; entry++) {

		if (atomic_read(&ch->n_to_notify) == 0)
			break;

		msg_slot = &ch->sn.uv.send_msg_slots[entry];
		if (msg_slot->func != NULL)
			xpc_notify_sender_uv(ch, msg_slot, ch->reason);
	}
}

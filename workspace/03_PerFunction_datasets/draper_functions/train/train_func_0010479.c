slurmdbd_pack_node_state_msg(dbd_node_state_msg_t *msg,
			     uint16_t rpc_version, Buf buffer)
{
	if (rpc_version >= SLURMDBD_2_3_VERSION) {
		pack32(msg->cpu_count, buffer);
		packstr(msg->hostlist, buffer);
		packstr(msg->reason, buffer);
		pack32(msg->reason_uid, buffer);
		pack16(msg->new_state, buffer);
		pack_time(msg->event_time, buffer);
		pack16(msg->state, buffer);
	}
}

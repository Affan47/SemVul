slurmdbd_pack_cluster_cpus_msg(dbd_cluster_cpus_msg_t *msg,
			       uint16_t rpc_version, Buf buffer)
{
	if (rpc_version >= SLURMDBD_2_5_VERSION) {
		packstr(msg->cluster_nodes, buffer);
		pack32(msg->cpu_count,    buffer);
		pack_time(msg->event_time, buffer);
	}
}

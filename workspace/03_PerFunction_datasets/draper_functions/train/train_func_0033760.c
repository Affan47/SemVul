_pack_trigger_msg(trigger_info_msg_t *msg , Buf buffer,
			      uint16_t protocol_version)
{
	int i;

	if (protocol_version >= SLURM_2_4_PROTOCOL_VERSION) {
		pack32(msg->record_count, buffer);
		for (i=0; i<msg->record_count; i++) {
			pack16 (msg->trigger_array[i].flags,     buffer);
			pack32 (msg->trigger_array[i].trig_id,   buffer);
			pack16 (msg->trigger_array[i].res_type,  buffer);
			packstr(msg->trigger_array[i].res_id,    buffer);
			pack32 (msg->trigger_array[i].trig_type, buffer);
			pack16 (msg->trigger_array[i].offset,    buffer);
			pack32 (msg->trigger_array[i].user_id,   buffer);
			packstr(msg->trigger_array[i].program,   buffer);
		}
	} else if (protocol_version >= SLURM_2_3_PROTOCOL_VERSION) {
		pack32(msg->record_count, buffer);
		for (i=0; i<msg->record_count; i++) {
			pack32 (msg->trigger_array[i].trig_id,   buffer);
			pack16 (msg->trigger_array[i].res_type,  buffer);
			packstr(msg->trigger_array[i].res_id,    buffer);
			pack32 (msg->trigger_array[i].trig_type, buffer);
			pack16 (msg->trigger_array[i].offset,    buffer);
			pack32 (msg->trigger_array[i].user_id,   buffer);
			packstr(msg->trigger_array[i].program,   buffer);
		}
	} else {
		error("_pack_trigger_msg: protocol_version "
		      "%hu not supported", protocol_version);
	}
}

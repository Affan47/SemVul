slurmdbd_pack_rc_msg(dbd_rc_msg_t *msg,
		     uint16_t rpc_version, Buf buffer)
{
	packstr(msg->comment, buffer);
	pack32(msg->return_code, buffer);
	pack16(msg->sent_type, buffer);
}

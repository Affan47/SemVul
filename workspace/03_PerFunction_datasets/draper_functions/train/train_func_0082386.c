get_msg_info(struct msg_info *msg_info, ulong shp, int id)
{
	char buf[BUFSIZE];

	msg_info->msg_queue = shp - OFFSET(msg_queue_q_perm);


	readmem(msg_info->msg_queue, KVADDR, buf, SIZE(msg_queue),
		"msg_queue", FAULT_ON_ERROR);

	msg_info->key = INT(buf + OFFSET(msg_queue_q_perm) +
			OFFSET(kern_ipc_perm_key));

	if (VALID_MEMBER(msg_queue_q_id))
		msg_info->msgid = INT(buf + OFFSET(msg_queue_q_id));
	else if (VALID_MEMBER(kern_ipc_perm_id))
		msg_info->msgid = INT(buf + OFFSET(msg_queue_q_perm) +
				OFFSET(kern_ipc_perm_id));
	else {
		ulong seq;
		seq = ULONG(buf + OFFSET(msg_queue_q_perm) +
				OFFSET(kern_ipc_perm_seq));
		msg_info->msgid = ipcs_table.seq_multiplier * seq + id;
	}

	msg_info->uid = UINT(buf + OFFSET(msg_queue_q_perm) +
			OFFSET(kern_ipc_perm_uid));

	if (BITS32())
		msg_info->perms = USHORT(buf + OFFSET(msg_queue_q_perm) +
				OFFSET(kern_ipc_perm_mode));
	else
		msg_info->perms = UINT(buf + OFFSET(msg_queue_q_perm) +
				OFFSET(kern_ipc_perm_mode));

	msg_info->bytes = ULONG(buf + OFFSET(msg_queue_q_cbytes));

	msg_info->messages = ULONG(buf + OFFSET(msg_queue_q_qnum));

	msg_info->deleted = UINT(buf + OFFSET(msg_queue_q_perm) +
				OFFSET(kern_ipc_perm_deleted));
}

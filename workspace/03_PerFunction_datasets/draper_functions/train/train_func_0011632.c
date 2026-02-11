cmd_post_perform(struct tgt_cmd_queue *q, struct scsi_cmd *cmd)
{
	q->active_cmd++;
	switch (cmd->attribute) {
	case MSG_ORDERED_TAG:
	case MSG_HEAD_TAG:
		set_queue_blocked(q);
		break;
	}
}

qla4_83xx_process_reset_template(struct scsi_qla_host *ha,
					     char *p_buff)
{
	int index, entries;
	struct qla4_83xx_reset_entry_hdr *p_hdr;
	char *p_entry = p_buff;

	ha->reset_tmplt.seq_end = 0;
	ha->reset_tmplt.template_end = 0;
	entries = ha->reset_tmplt.hdr->entries;
	index = ha->reset_tmplt.seq_index;

	for (; (!ha->reset_tmplt.seq_end) && (index  < entries); index++) {

		p_hdr = (struct qla4_83xx_reset_entry_hdr *)p_entry;
		switch (p_hdr->cmd) {
		case OPCODE_NOP:
			break;
		case OPCODE_WRITE_LIST:
			qla4_83xx_write_list(ha, p_hdr);
			break;
		case OPCODE_READ_WRITE_LIST:
			qla4_83xx_read_write_list(ha, p_hdr);
			break;
		case OPCODE_POLL_LIST:
			qla4_83xx_poll_list(ha, p_hdr);
			break;
		case OPCODE_POLL_WRITE_LIST:
			qla4_83xx_poll_write_list(ha, p_hdr);
			break;
		case OPCODE_READ_MODIFY_WRITE:
			qla4_83xx_read_modify_write(ha, p_hdr);
			break;
		case OPCODE_SEQ_PAUSE:
			qla4_83xx_pause(ha, p_hdr);
			break;
		case OPCODE_SEQ_END:
			qla4_83xx_seq_end(ha, p_hdr);
			break;
		case OPCODE_TMPL_END:
			qla4_83xx_template_end(ha, p_hdr);
			break;
		case OPCODE_POLL_READ_LIST:
			qla4_83xx_poll_read_list(ha, p_hdr);
			break;
		default:
			ql4_printk(KERN_ERR, ha, "%s: Unknown command ==> 0x%04x on entry = %d\n",
				   __func__, p_hdr->cmd, index);
			break;
		}


		p_entry += p_hdr->size;
	}

	ha->reset_tmplt.seq_index = index;
}

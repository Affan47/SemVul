print_sg_io_req(struct tcb *tcp, struct sg_io_hdr *sg_io)
{
	tprintf("{'%c', ", sg_io->interface_id);
	printxval(sg_io_dxfer_direction, sg_io->dxfer_direction,
		  "SG_DXFER_???");
	tprintf(", cmd[%u]=[", sg_io->cmd_len);
	print_sg_io_buffer(tcp, sg_io->cmdp, sg_io->cmd_len);
	tprintf("], mx_sb_len=%d, ", sg_io->mx_sb_len);
	tprintf("iovec_count=%d, ", sg_io->iovec_count);
	tprintf("dxfer_len=%u, ", sg_io->dxfer_len);
	tprintf("timeout=%u, ", sg_io->timeout);
	tprintf("flags=%#x", sg_io->flags);

	if (sg_io->dxfer_direction == SG_DXFER_TO_DEV ||
	    sg_io->dxfer_direction == SG_DXFER_TO_FROM_DEV) {
		tprintf(", data[%u]=[", sg_io->dxfer_len);
		printstr(tcp, (unsigned long) sg_io->dxferp,
			 sg_io->dxfer_len);
		tprintf("]");
	}
}

cim_pif_la_show(struct seq_file *seq, void *v, int idx)
{
	const u32 *p = v;

	if (v == SEQ_START_TOKEN) {
		seq_puts(seq, "Cntl ID DataBE   Addr                 Data\n");
	} else if (idx < CIM_PIFLA_SIZE) {
		seq_printf(seq, " %02x  %02x  %04x  %08x %08x%08x%08x%08x\n",
			   (p[5] >> 22) & 0xff, (p[5] >> 16) & 0x3f,
			   p[5] & 0xffff, p[4], p[3], p[2], p[1], p[0]);
	} else {
		if (idx == CIM_PIFLA_SIZE)
			seq_puts(seq, "\nCntl ID               Data\n");
		seq_printf(seq, " %02x  %02x %08x%08x%08x%08x\n",
			   (p[4] >> 6) & 0xff, p[4] & 0x3f,
			   p[3], p[2], p[1], p[0]);
	}
	return 0;
}

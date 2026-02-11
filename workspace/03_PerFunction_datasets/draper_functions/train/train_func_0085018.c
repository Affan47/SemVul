dbg_asicmode_show(struct seq_file *s, void *p)
{
	struct docg3 *docg3 = (struct docg3 *)s->private;

	int pctrl, mode;

	mutex_lock(&docg3->cascade->lock);
	pctrl = doc_register_readb(docg3, DOC_ASICMODE);
	mode = pctrl & 0x03;
	mutex_unlock(&docg3->cascade->lock);

	seq_printf(s,
		   "%04x : RAM_WE=%d,RSTIN_RESET=%d,BDETCT_RESET=%d,WRITE_ENABLE=%d,POWERDOWN=%d,MODE=%d%d (",
		   pctrl,
		   pctrl & DOC_ASICMODE_RAM_WE ? 1 : 0,
		   pctrl & DOC_ASICMODE_RSTIN_RESET ? 1 : 0,
		   pctrl & DOC_ASICMODE_BDETCT_RESET ? 1 : 0,
		   pctrl & DOC_ASICMODE_MDWREN ? 1 : 0,
		   pctrl & DOC_ASICMODE_POWERDOWN ? 1 : 0,
		   mode >> 1, mode & 0x1);

	switch (mode) {
	case DOC_ASICMODE_RESET:
		seq_puts(s, "reset");
		break;
	case DOC_ASICMODE_NORMAL:
		seq_puts(s, "normal");
		break;
	case DOC_ASICMODE_POWERDOWN:
		seq_puts(s, "powerdown");
		break;
	}
	seq_puts(s, ")\n");
	return 0;
}

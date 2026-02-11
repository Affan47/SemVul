bttv_risc_disasm(struct bttv *btv,
			     struct btcx_riscmem *risc)
{
	unsigned int i,j,n;

	pr_info("%s: risc disasm: %p [dma=0x%08lx]\n",
		btv->c.v4l2_dev.name, risc->cpu, (unsigned long)risc->dma);
	for (i = 0; i < (risc->size >> 2); i += n) {
		pr_info("%s:   0x%lx: ",
			btv->c.v4l2_dev.name,
			(unsigned long)(risc->dma + (i<<2)));
		n = bttv_risc_decode(le32_to_cpu(risc->cpu[i]));
		for (j = 1; j < n; j++)
			pr_info("%s:   0x%lx: 0x%08x [ arg #%d ]\n",
				btv->c.v4l2_dev.name,
				(unsigned long)(risc->dma + ((i+j)<<2)),
				risc->cpu[i+j], j);
		if (0 == risc->cpu[i])
			break;
	}
}

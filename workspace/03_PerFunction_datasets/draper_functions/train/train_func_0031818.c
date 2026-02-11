qla4_82xx_pci_set_crbwindow_2M(struct scsi_qla_host *ha, ulong *off)
{
	u32 win_read;

	ha->crb_win = CRB_HI(*off);
	writel(ha->crb_win,
		(void __iomem *)(CRB_WINDOW_2M + ha->nx_pcibase));


	win_read = readl((void __iomem *)(CRB_WINDOW_2M + ha->nx_pcibase));
	if (win_read != ha->crb_win) {
		DEBUG2(ql4_printk(KERN_INFO, ha,
		    "%s: Written crbwin (0x%x) != Read crbwin (0x%x),"
		    " off=0x%lx\n", __func__, ha->crb_win, win_read, *off));
	}
	*off = (*off & MASK(16)) + CRB_INDIRECT_2M + ha->nx_pcibase;
}

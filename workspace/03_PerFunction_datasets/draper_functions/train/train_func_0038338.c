myri10ge_dummy_rdma(struct myri10ge_priv *mgp, int enable)
{
	char __iomem *submit;
	__be32 buf[16] __attribute__ ((__aligned__(8)));
	u32 dma_low, dma_high;
	int i;


	mgp->cmd->data = 0;
	mb();


	dma_low = MYRI10GE_LOWPART_TO_U32(mgp->cmd_bus);
	dma_high = MYRI10GE_HIGHPART_TO_U32(mgp->cmd_bus);

	buf[0] = htonl(dma_high);
	buf[1] = htonl(dma_low);
	buf[2] = MYRI10GE_NO_CONFIRM_DATA;
	buf[3] = htonl(dma_high);
	buf[4] = htonl(dma_low);
	buf[5] = htonl(enable);

	submit = mgp->sram + MXGEFW_BOOT_DUMMY_RDMA;

	myri10ge_pio_copy(submit, &buf, sizeof(buf));
	for (i = 0; mgp->cmd->data != MYRI10GE_NO_CONFIRM_DATA && i < 20; i++)
		msleep(1);
	if (mgp->cmd->data != MYRI10GE_NO_CONFIRM_DATA)
		dev_err(&mgp->pdev->dev, "dummy rdma %s failed\n",
			(enable ? "enable" : "disable"));
}

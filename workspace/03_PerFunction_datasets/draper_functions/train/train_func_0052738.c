amd8111e_init_hw_default(struct amd8111e_priv *lp)
{
	unsigned int reg_val;
	void *mmio = lp->mmio;


	writel(RUN, mmio + CMD0);


	writel(0, mmio + RCV_RING_BASE_ADDR0);


	writel(0, mmio + XMT_RING_BASE_ADDR0);
	writel(0, mmio + XMT_RING_BASE_ADDR1);
	writel(0, mmio + XMT_RING_BASE_ADDR2);
	writel(0, mmio + XMT_RING_BASE_ADDR3);


	writel(CMD0_CLEAR, mmio + CMD0);


	writel(CMD2_CLEAR, mmio + CMD2);


	writel(CMD7_CLEAR, mmio + CMD7);


	writel(0x0, mmio + DLY_INT_A);
	writel(0x0, mmio + DLY_INT_B);


	writel(0x0, mmio + FLOW_CONTROL);


	reg_val = readl(mmio + INT0);
	writel(reg_val, mmio + INT0);


	writel(0x0, mmio + STVAL);


	writel(INTEN0_CLEAR, mmio + INTEN0);


	writel(0x0, mmio + LADRF);


	writel(0x80010, mmio + SRAM_SIZE);


	writel(0x0, mmio +  RCV_RING_LEN0);


	writel(0x0, mmio +  XMT_RING_LEN0);
	writel(0x0, mmio +  XMT_RING_LEN1);
	writel(0x0, mmio +  XMT_RING_LEN2);
	writel(0x0, mmio +  XMT_RING_LEN3);


	writel(0x0, mmio + XMT_RING_LIMIT);


	writew(MIB_CLEAR, mmio + MIB_ADDR);


	writel( 0, mmio + LADRF);
	writel( 0, mmio + LADRF + 4);


	reg_val = readl(mmio + SRAM_SIZE);


	writel(CTRL1_DEFAULT, mmio + CTRL1);


	readl(mmio + CMD2);
}

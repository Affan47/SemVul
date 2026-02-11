cas_phy_write(struct cas *cp, int reg, u16 val)
{
	int limit = STOP_TRIES_PHY;
	u32 cmd;

	cmd = MIF_FRAME_ST | MIF_FRAME_OP_WRITE;
	cmd |= CAS_BASE(MIF_FRAME_PHY_ADDR, cp->phy_addr);
	cmd |= CAS_BASE(MIF_FRAME_REG_ADDR, reg);
	cmd |= MIF_FRAME_TURN_AROUND_MSB;
	cmd |= val & MIF_FRAME_DATA_MASK;
	writel(cmd, cp->regs + REG_MIF_FRAME);


	while (limit-- > 0) {
		udelay(10);
		cmd = readl(cp->regs + REG_MIF_FRAME);
		if (cmd & MIF_FRAME_TURN_AROUND_LSB)
			return 0;
	}
	return -1;
}

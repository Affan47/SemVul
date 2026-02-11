serdes_wr(struct xgene_phy_ctx *ctx, int lane, u32 reg, u32 data)
{
	void __iomem *sds_base = ctx->sds_base;
	u32 val;

	reg += SERDES_INDIRECT_OFFSET;
	reg += lane * SERDES_LANE_STRIDE;
	sds_wr(sds_base, SATA_ENET_SDS_IND_CMD_REG,
	       SATA_ENET_SDS_IND_WDATA_REG, reg, data);
	sds_rd(sds_base, SATA_ENET_SDS_IND_CMD_REG,
	       SATA_ENET_SDS_IND_RDATA_REG, reg, &val);
	pr_debug("SERDES WR addr 0x%X value 0x%08X <-> 0x%08X\n", reg, data,
		 val);
}

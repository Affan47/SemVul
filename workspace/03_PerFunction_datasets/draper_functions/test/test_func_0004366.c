cg_in(struct clockgen *cg, u32 __iomem *reg)
{
	u32 val;

	if (cg->info.flags & CG_LITTLE_ENDIAN)
		val = ioread32(reg);
	else
		val = ioread32be(reg);

	return val;
}

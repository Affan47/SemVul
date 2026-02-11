write_kernel_doorbell(u32 __iomem *db, u32 value)
{
	if (db) {
		writel(value, db);
		pr_debug("writing %d to doorbell address 0x%p\n", value, db);
	}
}

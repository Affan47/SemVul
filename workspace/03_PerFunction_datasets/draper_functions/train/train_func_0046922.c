__t1_tpi_write(adapter_t *adapter, u32 addr, u32 value)
{
	int tpi_busy;

	writel(addr, adapter->regs + A_TPI_ADDR);
	writel(value, adapter->regs + A_TPI_WR_DATA);
	writel(F_TPIWR, adapter->regs + A_TPI_CSR);

	tpi_busy = t1_wait_op_done(adapter, A_TPI_CSR, F_TPIRDY, 1,
				   TPI_ATTEMPTS, 3);
	if (tpi_busy)
		pr_alert("%s: TPI write to 0x%x failed\n",
			 adapter->name, addr);
	return tpi_busy;
}

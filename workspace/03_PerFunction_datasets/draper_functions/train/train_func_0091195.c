start_spi_intr_handling(struct qcaspi *qca, u16 *intr_cause)
{
	*intr_cause = 0;

	qcaspi_write_register(qca, SPI_REG_INTR_ENABLE, 0);
	qcaspi_read_register(qca, SPI_REG_INTR_CAUSE, intr_cause);
	netdev_dbg(qca->net_dev, "interrupts: 0x%04x\n", *intr_cause);
}

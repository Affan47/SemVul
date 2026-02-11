dspi_data_to_pushr(struct fsl_dspi *dspi, int tx_word)
{
	u16 d16;

	if (!(dspi->dataflags & TRAN_STATE_TX_VOID))
		d16 = tx_word ? *(u16 *)dspi->tx : *(u8 *)dspi->tx;
	else
		d16 = dspi->void_write_data;

	dspi->tx += tx_word + 1;
	dspi->len -= tx_word + 1;

	return	SPI_PUSHR_TXDATA(d16) |
		SPI_PUSHR_PCS(dspi->cs) |
		SPI_PUSHR_CTAS(0) |
		SPI_PUSHR_CONT;
}

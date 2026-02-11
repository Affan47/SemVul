spu_read(struct if_spi_card *card, u16 reg, u8 *buf, int len)
{
	unsigned int delay;
	int err = 0;
	__le16 reg_out = cpu_to_le16(reg | IF_SPI_READ_OPERATION_MASK);
	struct spi_message m;
	struct spi_transfer reg_trans;
	struct spi_transfer dummy_trans;
	struct spi_transfer data_trans;


	BUG_ON(len & 0x1);

	spu_transaction_init(card);

	spi_message_init(&m);
	memset(&reg_trans, 0, sizeof(reg_trans));
	memset(&dummy_trans, 0, sizeof(dummy_trans));
	memset(&data_trans, 0, sizeof(data_trans));


	reg_trans.tx_buf = &reg_out;
	reg_trans.len = sizeof(reg_out);
	spi_message_add_tail(&reg_trans, &m);

	delay = spu_reg_is_port_reg(reg) ? card->spu_port_delay :
						card->spu_reg_delay;
	if (card->use_dummy_writes) {

		dummy_trans.len = delay / 8;
		spi_message_add_tail(&dummy_trans, &m);
	} else {

		reg_trans.delay_usecs =
			DIV_ROUND_UP((100 + (delay * 10)), 1000);
	}


	data_trans.rx_buf = buf;
	data_trans.len = len;
	spi_message_add_tail(&data_trans, &m);

	err = spi_sync(card->spi, &m);
	spu_transaction_finish(card);
	return err;
}

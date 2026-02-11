init_idt43102(struct mc5 *mc5)
{
	int i;
	struct adapter *adap = mc5->adapter;

	t3_write_reg(adap, A_MC5_DB_RSP_LATENCY,
		     adap->params.rev == 0 ? V_RDLAT(0xd) | V_SRCHLAT(0x11) :
		     V_RDLAT(0xd) | V_SRCHLAT(0x12));


	t3_write_reg(adap, A_MC5_DB_POPEN_DATA_WR_CMD, IDT4_CMD_WRITE);
	t3_write_reg(adap, A_MC5_DB_POPEN_MASK_WR_CMD, IDT4_CMD_WRITE);
	t3_write_reg(adap, A_MC5_DB_AOPEN_SRCH_CMD,
		     IDT4_CMD_SEARCH144 | 0x3800);
	t3_write_reg(adap, A_MC5_DB_SYN_SRCH_CMD, IDT4_CMD_SEARCH144);
	t3_write_reg(adap, A_MC5_DB_ACK_SRCH_CMD, IDT4_CMD_SEARCH144 | 0x3800);
	t3_write_reg(adap, A_MC5_DB_ILOOKUP_CMD, IDT4_CMD_SEARCH144 | 0x3800);
	t3_write_reg(adap, A_MC5_DB_ELOOKUP_CMD, IDT4_CMD_SEARCH144 | 0x800);
	t3_write_reg(adap, A_MC5_DB_DATA_WRITE_CMD, IDT4_CMD_WRITE);
	t3_write_reg(adap, A_MC5_DB_DATA_READ_CMD, IDT4_CMD_READ);

	t3_write_reg(adap, A_MC5_DB_PART_ID_INDEX, 3);


	t3_write_reg(adap, A_MC5_DB_DBGI_CONFIG, DBGI_MODE_IDT52100);


	dbgi_wr_data3(adap, 0xffffffff, 0xffffffff, 0xff);
	for (i = 0; i < 7; ++i)
		if (mc5_write(adap, IDT4_GMR_BASE0 + i, IDT4_CMD_WRITE))
			goto err;

	for (i = 0; i < 4; ++i)
		if (mc5_write(adap, IDT4_GMR_BASE2 + i, IDT4_CMD_WRITE))
			goto err;

	dbgi_wr_data3(adap, 0xfffffff9, 0xffffffff, 0xff);
	if (mc5_write(adap, IDT4_GMR_BASE1, IDT4_CMD_WRITE) ||
	    mc5_write(adap, IDT4_GMR_BASE1 + 1, IDT4_CMD_WRITE) ||
	    mc5_write(adap, IDT4_GMR_BASE1 + 4, IDT4_CMD_WRITE))
		goto err;

	dbgi_wr_data3(adap, 0xfffffff9, 0xffff8007, 0xff);
	if (mc5_write(adap, IDT4_GMR_BASE1 + 5, IDT4_CMD_WRITE))
		goto err;


	dbgi_wr_data3(adap, 0xf0000000, 0, 0);
	if (mc5_write(adap, IDT4_SCR_ADR0, IDT4_CMD_WRITE))
		goto err;

	return init_mask_data_array(mc5, IDT4_MSKARY_BASE_ADR0,
				    IDT4_DATARY_BASE_ADR0, IDT4_CMD_WRITE, 1);
err:
	return -EIO;
}

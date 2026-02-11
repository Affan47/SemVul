s2io_set_swapper(struct s2io_nic *sp)
{
	struct net_device *dev = sp->dev;
	struct XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64, valt, valr;


	val64 = readq(&bar0->pif_rd_swapper_fb);
	if (val64 != 0x0123456789ABCDEFULL) {
		int i = 0;
		static const u64 value[] = {
			0xC30000C3C30000C3ULL,
			0x8100008181000081ULL,
			0x4200004242000042ULL,
			0
		};

		while (i < 4) {
			writeq(value[i], &bar0->swapper_ctrl);
			val64 = readq(&bar0->pif_rd_swapper_fb);
			if (val64 == 0x0123456789ABCDEFULL)
				break;
			i++;
		}
		if (i == 4) {
			DBG_PRINT(ERR_DBG, "%s: Endian settings are wrong, "
				  "feedback read %llx\n",
				  dev->name, (unsigned long long)val64);
			return FAILURE;
		}
		valr = value[i];
	} else {
		valr = readq(&bar0->swapper_ctrl);
	}

	valt = 0x0123456789ABCDEFULL;
	writeq(valt, &bar0->xmsi_address);
	val64 = readq(&bar0->xmsi_address);

	if (val64 != valt) {
		int i = 0;
		static const u64 value[] = {
			0x00C3C30000C3C300ULL,
			0x0081810000818100ULL,
			0x0042420000424200ULL,
			0
		};

		while (i < 4) {
			writeq((value[i] | valr), &bar0->swapper_ctrl);
			writeq(valt, &bar0->xmsi_address);
			val64 = readq(&bar0->xmsi_address);
			if (val64 == valt)
				break;
			i++;
		}
		if (i == 4) {
			unsigned long long x = val64;
			DBG_PRINT(ERR_DBG,
				  "Write failed, Xmsi_addr reads:0x%llx\n", x);
			return FAILURE;
		}
	}
	val64 = readq(&bar0->swapper_ctrl);
	val64 &= 0xFFFF000000000000ULL;

#ifdef __BIG_ENDIAN


	val64 |= (SWAPPER_CTRL_TXP_FE |
		  SWAPPER_CTRL_TXP_SE |
		  SWAPPER_CTRL_TXD_R_FE |
		  SWAPPER_CTRL_TXD_W_FE |
		  SWAPPER_CTRL_TXF_R_FE |
		  SWAPPER_CTRL_RXD_R_FE |
		  SWAPPER_CTRL_RXD_W_FE |
		  SWAPPER_CTRL_RXF_W_FE |
		  SWAPPER_CTRL_XMSI_FE |
		  SWAPPER_CTRL_STATS_FE |
		  SWAPPER_CTRL_STATS_SE);
	if (sp->config.intr_type == INTA)
		val64 |= SWAPPER_CTRL_XMSI_SE;
	writeq(val64, &bar0->swapper_ctrl);
#else


	val64 |= (SWAPPER_CTRL_TXP_FE |
		  SWAPPER_CTRL_TXP_SE |
		  SWAPPER_CTRL_TXD_R_FE |
		  SWAPPER_CTRL_TXD_R_SE |
		  SWAPPER_CTRL_TXD_W_FE |
		  SWAPPER_CTRL_TXD_W_SE |
		  SWAPPER_CTRL_TXF_R_FE |
		  SWAPPER_CTRL_RXD_R_FE |
		  SWAPPER_CTRL_RXD_R_SE |
		  SWAPPER_CTRL_RXD_W_FE |
		  SWAPPER_CTRL_RXD_W_SE |
		  SWAPPER_CTRL_RXF_W_FE |
		  SWAPPER_CTRL_XMSI_FE |
		  SWAPPER_CTRL_STATS_FE |
		  SWAPPER_CTRL_STATS_SE);
	if (sp->config.intr_type == INTA)
		val64 |= SWAPPER_CTRL_XMSI_SE;
	writeq(val64, &bar0->swapper_ctrl);
#endif
	val64 = readq(&bar0->swapper_ctrl);


	val64 = readq(&bar0->pif_rd_swapper_fb);
	if (val64 != 0x0123456789ABCDEFULL) {

		DBG_PRINT(ERR_DBG,
			  "%s: Endian settings are wrong, feedback read %llx\n",
			  dev->name, (unsigned long long)val64);
		return FAILURE;
	}

	return SUCCESS;
}

scc_read_reg(int port, double dcycs)
{
	Scc	*scc_ptr;
	word32	ret;
	int	regnum;

	scc_ptr = &(scc_stat[port]);
	scc_ptr->mode = 0;
	regnum = scc_ptr->reg_ptr;


	switch(regnum) {
	case 0:
	case 4:
		ret = 0x60;
		if(scc_ptr->dcd) {
			ret |= 0x08;
		}
		ret |= 0x8;
		if(scc_ptr->rx_queue_depth) {
			ret |= 0x01;
		}
		if(scc_ptr->tx_buf_empty) {
			ret |= 0x04;
		}
		if(scc_ptr->br_is_zero) {
			ret |= 0x02;
		}

		break;
	case 1:
	case 5:

		ret = 0x07;
		break;
	case 2:
	case 6:
		if(port == 0) {
			ret = scc_ptr->reg[2];
		} else {

			halt_printf("Read of RR2B...stopping\n");
			ret = 0;
#if 0
			ret = scc_stat[0].reg[2];
			wr9 = scc_stat[0].reg[9];
			for(i = 0; i < 8; i++) {
				if(ZZZ){};
			}
			if(wr9 & 0x10) {


			}
#endif
		}
		break;
	case 3:
	case 7:
		if(port == 0) {
			ret = (g_irq_pending & 0x3f);
		} else {
			ret = 0;
		}
		break;
	case 8:
		ret = scc_read_data(port, dcycs);
		break;
	case 9:
	case 13:
		ret = scc_ptr->reg[13];
		break;
	case 10:
	case 14:
		ret = 0;
		break;
	case 11:
	case 15:
		ret = scc_ptr->reg[15];
		break;
	case 12:
		ret = scc_ptr->reg[12];
		break;
	default:
		halt_printf("Tried reading c03%x with regnum: %d!\n", 8+port,
			regnum);
		ret = 0;
	}

	scc_ptr->reg_ptr = 0;
	scc_printf("Read c03%x, rr%d, ret: %02x\n", 8+port, regnum, ret);
	if(regnum != 0 && regnum != 3) {
		scc_log(SCC_REGNUM(0,port,regnum), ret, dcycs);
	}

	return ret;
}

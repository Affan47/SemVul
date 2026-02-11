stv0900_set_viterbi_standard(struct stv0900_internal *intp,
				   enum fe_stv0900_search_standard standard,
				   enum fe_stv0900_fec fec,
				   enum fe_stv0900_demod_num demod)
{
	dprintk("%s: ViterbiStandard = ", __func__);

	switch (standard) {
	case STV0900_AUTO_SEARCH:
		dprintk("Auto\n");
		stv0900_write_reg(intp, FECM, 0x10);
		stv0900_write_reg(intp, PRVIT, 0x3f);
		break;
	case STV0900_SEARCH_DVBS1:
		dprintk("DVBS1\n");
		stv0900_write_reg(intp, FECM, 0x00);
		switch (fec) {
		case STV0900_FEC_UNKNOWN:
		default:
			stv0900_write_reg(intp, PRVIT, 0x2f);
			break;
		case STV0900_FEC_1_2:
			stv0900_write_reg(intp, PRVIT, 0x01);
			break;
		case STV0900_FEC_2_3:
			stv0900_write_reg(intp, PRVIT, 0x02);
			break;
		case STV0900_FEC_3_4:
			stv0900_write_reg(intp, PRVIT, 0x04);
			break;
		case STV0900_FEC_5_6:
			stv0900_write_reg(intp, PRVIT, 0x08);
			break;
		case STV0900_FEC_7_8:
			stv0900_write_reg(intp, PRVIT, 0x20);
			break;
		}

		break;
	case STV0900_SEARCH_DSS:
		dprintk("DSS\n");
		stv0900_write_reg(intp, FECM, 0x80);
		switch (fec) {
		case STV0900_FEC_UNKNOWN:
		default:
			stv0900_write_reg(intp, PRVIT, 0x13);
			break;
		case STV0900_FEC_1_2:
			stv0900_write_reg(intp, PRVIT, 0x01);
			break;
		case STV0900_FEC_2_3:
			stv0900_write_reg(intp, PRVIT, 0x02);
			break;
		case STV0900_FEC_6_7:
			stv0900_write_reg(intp, PRVIT, 0x10);
			break;
		}
		break;
	default:
		break;
	}
}

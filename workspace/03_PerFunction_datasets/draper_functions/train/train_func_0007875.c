ctrl_body_print(u_int16_t fc, const u_char *p)
{
	switch (FC_SUBTYPE(fc)) {
	case CTRL_CONTROL_WRAPPER:
		printf("Control Wrapper");

		break;
	case CTRL_BAR:
		printf("BAR");
		if (!TTEST2(*p, CTRL_BAR_HDRLEN))
			return 0;
		if (!eflag)
			printf(" RA:%s TA:%s CTL(%x) SEQ(%u) ",
			    etheraddr_string(((const struct ctrl_bar_t *)p)->ra),
			    etheraddr_string(((const struct ctrl_bar_t *)p)->ta),
			    EXTRACT_LE_16BITS(&(((const struct ctrl_bar_t *)p)->ctl)),
			    EXTRACT_LE_16BITS(&(((const struct ctrl_bar_t *)p)->seq)));
		break;
	case CTRL_BA:
		printf("BA");
		if (!TTEST2(*p, CTRL_BA_HDRLEN))
			return 0;
		if (!eflag)
			printf(" RA:%s ",
			    etheraddr_string(((const struct ctrl_ba_t *)p)->ra));
		break;
	case CTRL_PS_POLL:
		printf("Power Save-Poll");
		if (!TTEST2(*p, CTRL_PS_POLL_HDRLEN))
			return 0;
		printf(" AID(%x)",
		    EXTRACT_LE_16BITS(&(((const struct ctrl_ps_poll_t *)p)->aid)));
		break;
	case CTRL_RTS:
		printf("Request-To-Send");
		if (!TTEST2(*p, CTRL_RTS_HDRLEN))
			return 0;
		if (!eflag)
			printf(" TA:%s ",
			    etheraddr_string(((const struct ctrl_rts_t *)p)->ta));
		break;
	case CTRL_CTS:
		printf("Clear-To-Send");
		if (!TTEST2(*p, CTRL_CTS_HDRLEN))
			return 0;
		if (!eflag)
			printf(" RA:%s ",
			    etheraddr_string(((const struct ctrl_cts_t *)p)->ra));
		break;
	case CTRL_ACK:
		printf("Acknowledgment");
		if (!TTEST2(*p, CTRL_ACK_HDRLEN))
			return 0;
		if (!eflag)
			printf(" RA:%s ",
			    etheraddr_string(((const struct ctrl_ack_t *)p)->ra));
		break;
	case CTRL_CF_END:
		printf("CF-End");
		if (!TTEST2(*p, CTRL_END_HDRLEN))
			return 0;
		if (!eflag)
			printf(" RA:%s ",
			    etheraddr_string(((const struct ctrl_end_t *)p)->ra));
		break;
	case CTRL_END_ACK:
		printf("CF-End+CF-Ack");
		if (!TTEST2(*p, CTRL_END_ACK_HDRLEN))
			return 0;
		if (!eflag)
			printf(" RA:%s ",
			    etheraddr_string(((const struct ctrl_end_ack_t *)p)->ra));
		break;
	default:
		printf("Unknown Ctrl Subtype");
	}
	return 1;
}

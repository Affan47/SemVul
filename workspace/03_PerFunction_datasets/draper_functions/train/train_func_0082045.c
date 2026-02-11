vt_ctrl_DECTST(struct cpssp *cpssp, unsigned int p1, unsigned int p2)
{
	if (p1 == 2) {
		switch(p2) {
		case 1:
			vt_init(cpssp);
			break;
		case 2:
		case 4:
		case 16:
		case 9:
		case 10:
		case 12:
		case 24:
			TRACE("unsupported confidence test: %u\n", p2);
			break;
		default:
			TRACE("unknown confidence test: %u\n", p2);
			break;
		}
	} else {
		TRACE("unknown DECTST parameters: %u %u\n", p1, p2);
	}
}

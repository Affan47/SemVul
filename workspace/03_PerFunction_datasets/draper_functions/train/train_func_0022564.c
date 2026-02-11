_rtl_get_hal_qnum(u16 queue)
{
	int qnum;

	switch (queue) {
	case 0:
		qnum = AC3_VO;
		break;
	case 1:
		qnum = AC2_VI;
		break;
	case 2:
		qnum = AC0_BE;
		break;
	case 3:
		qnum = AC1_BK;
		break;
	default:
		qnum = AC0_BE;
		break;
	}
	return qnum;
}

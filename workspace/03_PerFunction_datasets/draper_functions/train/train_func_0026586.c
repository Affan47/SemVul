l3dss1_std_ie_err(struct l3_process *pc, int ret) {

	if (pc->debug & L3_DEB_CHECK)
		l3_debug(pc->st, "check_infoelements ret %d", ret);
	switch (ret) {
	case 0:
		break;
	case ERR_IE_COMPREHENSION:
		pc->para.cause = 96;
		l3dss1_status_send(pc, 0, NULL);
		break;
	case ERR_IE_UNRECOGNIZED:
		pc->para.cause = 99;
		l3dss1_status_send(pc, 0, NULL);
		break;
	case ERR_IE_LENGTH:
		pc->para.cause = 100;
		l3dss1_status_send(pc, 0, NULL);
		break;
	case ERR_IE_SEQUENCE:
	default:
		break;
	}
}

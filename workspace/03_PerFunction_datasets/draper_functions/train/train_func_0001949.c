pptp_err_code_print(const u_int8_t *err_code)
{
	printf(" ERR_CODE(%u", *err_code);
	if (vflag) {
		switch (*err_code) {
		case 0:
			printf(":None");
			break;
		case 1:
			printf(":Not-Connected");
			break;
		case 2:
			printf(":Bad-Format");
			break;
		case 3:
			printf(":Bad-Valude");
			break;
		case 4:
			printf(":No-Resource");
			break;
		case 5:
			printf(":Bad-Call-ID");
			break;
		case 6:
			printf(":PAC-Error");
			break;
		default:
			printf(":?");
			break;
		}
	}
	printf(")");
}

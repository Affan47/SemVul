field_count_reply(int ot, int posit, Octstr *whoami)
{
    switch(ot) {
    case 01:
	return posit ? 2 : 3;
    case 31:
	return posit ? 2 : 3;
    case 51:
    case 52:
    case 53:
	return 3;
    case 60:
	return posit ? 2 : 3;
    default:
	error(0, "EMI2[%s]: Unsupported EMI operation reply type %d",
	      octstr_get_cstr(whoami), ot);
	return -1;
    }
}

rpq_dump_warnings(void)
{

	if (!rpq_complained && rpq_wbcnt) {
		popup_an_error("%s", rpq_warnbuf);
		rpq_wbcnt = 0;
		rpq_complained = True;

		free(rpq_warnbuf);
		rpq_warnbuf = CN;
	}
}

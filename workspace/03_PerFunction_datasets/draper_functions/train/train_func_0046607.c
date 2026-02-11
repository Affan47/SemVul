doc_log_rout(char *msg, int osc, double dsamps, int etc)
{
	int	pos;

	pos = g_doc_log_pos;
	g_doc_log[pos].msg = msg;
	g_doc_log[pos].osc = osc;
	g_doc_log[pos].dsamps = dsamps;
	g_doc_log[pos].dtmp2 = g_last_sound_play_dsamp;
	g_doc_log[pos].etc = etc;
	if(osc >= 0 && osc < 32) {
		g_doc_log[pos].doc_reg = g_doc_regs[osc];
	}
	pos++;
	if(pos >= LEN_DOC_LOG) {
		pos = 0;
	}

	doc_printf("log: %s, osc:%d dsamp:%f, etc:%d\n", msg, osc, dsamps, etc);

	g_doc_log_pos = pos;
}

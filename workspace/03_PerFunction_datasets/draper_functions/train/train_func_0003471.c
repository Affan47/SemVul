f_eof(int chn) throw(ParserError) {
	if (f_testchan(chn) == -1) return 1;
	else return (int)g_Files[chn]->eof();
}

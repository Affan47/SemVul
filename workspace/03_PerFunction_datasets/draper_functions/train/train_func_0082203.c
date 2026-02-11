show_results(void)
{
	static SDSTRING common = { 0, "" };
	const char *errmsg;

	if (compl.cnt == 0) {
		done = 1;
		switch (compl.err) {
		case 0:
			errmsg = " (no match)";
			break;
		case EACCES:
			errmsg = " (permission denied)";
			break;
		case ENOENT:
			errmsg = " (no such directory)";
			break;
		default:
			errmsg = "";
		}
		win_remark_fmt("cannot complete that %s%s",
		  code2string(rq.type,0),errmsg);
		return;
	}

	if (compl.cnt == 1) {
		insert_candidate(0);
		return;
	}

	if (compl.clen) {

		sd_copyn(&common,SDSTR(CC_LIST[0].str) + rq.strlen,compl.clen);
		edit_insertstr(SDSTR(common),compl.quote);


		rq.strlen += compl.clen;

	}

	if (compl.cnt <= cc_max) {
		control_loop(MODE_COMPL);
		return;
	}


	win_completion(compl.cnt,compl.clen ? 0 : compl.first_char);
}

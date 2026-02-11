remember_line(gchar *file, gint page, gint line, gint offset, gchar *heading, gchar *word, gint code){
	RESULT *rp;
	gchar *tmp;
	gchar *p;
	gchar *start;
	gint i;
	gchar buff[512];
	gchar *here;

	LOG(LOG_DEBUG, "IN : remember_line(%s, %d, %s, %s, %d)", file, line, heading, word, code);

	rp = g_new0(RESULT,1);

	p = heading;
	while((*p == ' ') || (*p == '\t'))
		p++;

	switch(code){

	case KCODE_EUC:
		tmp = iconv_convert2("euc-jp", "utf-8", p);
		break;
	case KCODE_JIS:
		tmp = iconv_convert2("iso-2022-jp", "utf-8", p);
		break;
	case KCODE_SJIS:
		tmp = iconv_convert2("Shift_JIS", "utf-8", p);
		break;
	case KCODE_ASCII:
		tmp = remove_non_ascii(heading);
		break;
	default:
		g_free(rp->word);
		g_free(rp);
		return;
		break;
	}

	rp->word = iconv_convert("euc-jp", "utf-8", word);


	here = (gchar *) simple_search((guchar *) rp->word, (guchar *) tmp, strlen(tmp), bignore_case);
	if(here != NULL){
		p = here;
		for(i=0; i < additional_chars ; i ++){
			p = g_utf8_find_prev_char(tmp, p);
			if(p == NULL) {
				p = tmp;
				break;
			}
		}
		start = p;

		if(start != tmp){
			strcpy(buff, "....");
			g_utf8_strncpy(&buff[4], start, additional_chars*2+g_utf8_strlen(word, -1));
		} else {
			g_utf8_strncpy(buff, start, additional_chars + i + g_utf8_strlen(word, -1));
		}

		if(g_utf8_strlen(buff, -1) == additional_chars*2+g_utf8_strlen(word, -1))
			strcat(buff, "....");

		rp->heading = strdup(buff);
		g_free(tmp);
	} else {
		rp->heading = tmp;
	}

	rp->type = RESULT_TYPE_GREP;
	rp->data.grep.filename = native_to_generic(file);

	rp->data.grep.page = page;
	rp->data.grep.line = line;
	rp->data.grep.offset = offset;

	add_result(rp);

	LOG(LOG_DEBUG, "OUT : remember_line()");
}

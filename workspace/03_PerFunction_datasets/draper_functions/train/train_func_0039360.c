adjustline(char* line, struct entry* e,
	struct reply_packet* pkt)
{
	char* parse = line;
	while(*parse) {
		if(isendline(*parse))
			return;
		if(str_keyword(&parse, "copy_id")) {
			e->copy_id = true;
		} else if(str_keyword(&parse, "copy_query")) {
			e->copy_query = true;
		} else if(str_keyword(&parse, "sleep=")) {
			e->sleeptime = (unsigned int) strtol(parse, (char**)&parse, 10);
			while(isspace((int)*parse))
				parse++;
		} else if(str_keyword(&parse, "packet_sleep=")) {
			pkt->packet_sleep = (unsigned int) strtol(parse, (char**)&parse, 10);
			while(isspace((int)*parse))
				parse++;
		} else {
			error("could not parse ADJUST: '%s'", parse);
		}
	}
}

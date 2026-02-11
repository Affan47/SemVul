zParseRanges(const char* l) {
	char* list;

	char* start;
	char* div;
	char* end;
	char *err1, *err2;

	int start_num, end_num;

	zSFVec* result = NULL;
	zSfeature cur;


	result = zMalloc(sizeof(zSFVec), "zParseRanges: result vector");

	zInitSFVec(result, 1);
	if (l == NULL) {
		zFree(result->elem);
		result->elem=NULL;
		return result;
	}

	cur.name = -1; cur.state = 0; cur.score = 0;
	cur.lfrag = cur.rfrag = cur.frame = 0;
	cur.group = NULL;


	list = zMalloc((strlen(l)+2)*sizeof(char), "zParseRanges: copy arg");
	strcpy(list, l); *(list+strlen(l)+1) = '\0';

	start = div = end = list;
	while (*start != '\0') {

		while (*end != ',' && *end != '\0') ++end;
		*end = '\0';

		while (*div != ':' && *div != '\0') ++div;
		*div = '\0';


		cur.strand = '+';
		start_num = strtol(start, &err1, 10);
		if (err1 != div || start == div) {
			zDie("Couldn't read \"%s\" as a number", start);
		}
		if (end == div || end == div+1) {
			end_num = start_num;
		} else {
			end_num = strtol(div+1, &err2, 10);
			if (err2 != end) {
				zDie("Couldn't read \"%s\" as an upperlimit", div+1);
			}
		}
		if (start_num == 0 || end_num == 0) {
			zDie("Zero is an illegal coordinate");
		}


		if (start_num < 0) {
			cur.start = -start_num - 1;
			cur.strand = '-';
		} else {
			cur.start = start_num - 1;
		}
		if (end_num < 0) {
			cur.end = -end_num - 1;
			cur.strand = '-';
		} else {
			cur.end = end_num - 1;
		}
		zPushSFVec (result, &cur);

		start = div = end = end+1;
	}

	zFree(list);
	return result;
}

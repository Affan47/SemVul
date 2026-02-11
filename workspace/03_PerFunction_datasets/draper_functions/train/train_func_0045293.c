read_db(fp)

FILE *fp;
{
    char buf[BSIZE], *s, *t, *kw = NULL, *ti = NULL;
    struct sHlpEnt *bb = NULL;
    int keyword = 0, title = 0;

    while ((s = my_fgets(buf, BSIZE, fp)) != NULL) {

        if (prefix(HLP_KEYWORD,buf)) {
            keyword = true;
            title = false;
            kw = NULL;
            continue;
        }
        if (prefix(HLP_TITLE,buf)) {
            title = true;
            keyword = false;
            ti = NULL;
            continue;
        }
        if (prefix(HLP_TEXT,buf)) {
            if (ti && kw) {

                if (HelpBase == NULL) {
                    HelpBase = alloc(sHlpEnt);
                    bb = HelpBase;
                }
                else {
                    bb->next = alloc(sHlpEnt);
                    bb = bb->next;
                }
                bb->next = NULL;
                bb->keyword = kw;
                bb->title = ti;
                bb->offset = ftell(fp);
                ti = NULL;
                kw = NULL;
                keyword = false;
                title = false;
            }
            continue;
        }

        if (keyword || title) {

            while (isspace(*s))
                s++;
            if (!*s)
                continue;

	    t = s + strlen(s)-1;
	    while (*t <= ' ')
		*t-- = '\0';

            if (keyword)
                kw = copy(s);
            else
                ti = copy(s);

        }
    }
}

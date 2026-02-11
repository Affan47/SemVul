html_sanitise_filename(htmlfilelist *files, char *text)
{


    char *p = text, *q = text;

    while (*p) {
	if ((*p>='A' && *p<='Z') ||
	    (*p>='a' && *p<='z') ||
	    (*p>='0' && *p<='9') ||
	    *p=='-' || *p=='_' || *p=='+' || *p=='.' || *p=='=')
	    *q++ = *p;
	p++;
    }
    *q = '\0';


    if (!*text) {
	static const char anonfrag[] = "anon.html";
	text = sresize(text, lenof(anonfrag), char);
	strcpy(text, anonfrag);
    }


    {
	int len, extpos;
	int suffix = 1;

	p = NULL;

	while (find234(files->files, text, NULL)) {
	    if (!p) {
		len = strlen(text);
		p = text;
		text = snewn(len+20, char);

		for (extpos = len; extpos > 0 && p[extpos-1] != '.'; extpos--);
		if (extpos > 0)
		    extpos--;
		else
		    extpos = len;
	    }

	    sprintf(text, "%.*s-%d%s", extpos, p, ++suffix, p+extpos);
	}

	if (p)
	    sfree(p);
    }

    return text;
}

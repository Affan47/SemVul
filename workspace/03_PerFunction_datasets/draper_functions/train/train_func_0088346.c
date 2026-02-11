LoadHelp(char *path)
{
    LINKEY *key = 0;
    long pos = 0;
    char buf[BUFSIZ];
    LINEBUF *head;
    LINEBUF *firsthead = NULL;
    TBOOLEAN primary;
    TBOOLEAN flag;

    if ((helpfp = fopen(path, "r")) == NULL) {

	return (H_ERROR);
    }


    if (!fgets(buf, BUFSIZ - 1, helpfp) || *buf != KEYFLAG)
	return (H_ERROR);

    while (!feof(helpfp)) {


	primary = TRUE;
	while (buf[0] == KEYFLAG) {
	    key = storekey(buf + 1);
	    key->primary = primary;
	    key->text = NULL;
	    key->pos = 0;
	    primary = FALSE;
	    pos = ftell(helpfp);
	    if (fgets(buf, BUFSIZ - 1, helpfp) == (char *) NULL)
		break;
	}


	firsthead = storeline(buf);
	head = firsthead;
	while ((fgets(buf, BUFSIZ - 1, helpfp) != (char *) NULL)
	       && (buf[0] != KEYFLAG)) {

	    head->next = storeline(buf);
	    head = head->next;
	}

	do {
	    key->pos = pos;
	    key->text = firsthead;
	    flag = key->primary;
	    key = key->next;
	} while (flag != TRUE && key != NULL);
    }
    (void) fclose(helpfp);


    sortkeys();
    return (H_FOUND);
}

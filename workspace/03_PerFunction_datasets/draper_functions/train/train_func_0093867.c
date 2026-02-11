Expire(SortedInput, qp)
    BOOL		SortedInput;
    register QIOSTATE	*qp;
{
    static LIST		List;
    register char	*line;
    register char	*p;
    char		group[SPOOLNAMEBUFF];

    if (List.Articles == NULL) {
	List.Size = START_LIST_SIZE;
	List.Articles = NEW(ARTNUM, List.Size);
    }
    List.Used = 0;

    if (SortedInput) {
	for ( ; ; ) {
	    if ((line = QIOread(qp)) == NULL) {
		if (QIOerror(qp)) {
		    (void)fprintf(stderr, "Can't read input %s\n",
			    strerror(errno));
		    break;
		}
		if (QIOtoolong(qp))
		    continue;
		break;
	    }
	    if ((p = strrchr(line, '/')) == NULL)
		continue;
	    *p++ = '\0';
	    if (List.Used == 0) {
		(void)strcpy(group, line);
		List.Used = 0;
	    }
	    else if (!EQ(line, group)) {
		LISTsort(&List);
		RemoveLines(group, &List);
		(void)strcpy(group, line);
		List.Used = 0;
	    }
	    LISTappend(List, atol(p));
	}


	if (List.Used) {
	    LISTsort(&List);
	    RemoveLines(group, &List);
	}
    }
    else {
	for (List.Used = 1; ; ) {
	    if ((line = QIOread(qp)) == NULL) {
		if (QIOerror(qp)) {
		    (void)fprintf(stderr, "Can't read input %s\n",
			    strerror(errno));
		    break;
		}
		if (QIOtoolong(qp))
		    continue;
		break;
	    }
	    if ((p = strrchr(line, '/')) == NULL)
		continue;
	    *p++ = '\0';
	    List.Articles[0] = atol(p);
	    RemoveLines(line, &List);
	}
    }

    QIOclose(qp);
}

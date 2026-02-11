parse_text_position_argument(const char *argument, EB_Position *text_position)
{
    const char *p = argument;
    const char *end_p;
    int page;
    int offset;


    while (*p == ' ' || *p == '\t')
	p++;

    if (*p == '0' && (*(p + 1) == 'x' || *(p + 1) == 'X'))
	p += 2;
    page = strtol(p, (char **)&end_p, 16);
    if (end_p == p || *end_p != ':')
	goto failed;
    if (page <= 0)
	goto failed;


    p = end_p + 1;

    if (*p == '0' && (*(p + 1) == 'x' || *(p + 1) == 'X'))
	p += 2;
    offset = strtol(p, (char **)&end_p, 16);
    if (end_p == p)
	goto failed;
    while (*end_p == ' ' || *end_p == '\t')
	end_p++;
    if (*end_p != '\0')
	goto failed;
    if (offset < 0 || EB_SIZE_PAGE <= offset)
	goto failed;

    text_position->page = page;
    text_position->offset = offset;

    return 0;


  failed:
    fprintf(stderr, _("%s: invalid text position `%s'\n"), invoked_name,
	argument);
    return -1;
}

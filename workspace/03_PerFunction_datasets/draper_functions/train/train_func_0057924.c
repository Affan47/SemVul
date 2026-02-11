parse_comment(Parser p, int skip)
{
    InputSource s = p->source;
    int c, c1=0, c2=0;
    int count = 0;

    if(!skip)
	p->pbufnext = 0;

    while((c = get(s)) != XEOE)
    {
	count++;
	if(c1 == '-' && c2 == '-')
	{
	    if(c == '>')
		break;
	    unget(s);
	    return error(p, "-- in comment");
	}

	if(at_eol(s))
	{
	    if(!skip)
	    {
		require(transcribe(p, count, count));
	    }
	    count = 0;
	}
	c2 = c1; c1 = c;
    }

    if(c == XEOE)
	return error(p, "EOE in comment");

    if(skip)
	return 0;

    require(transcribe(p, count, count-3));
    p->pbuf[p->pbufnext++] = 0;
    p->xbit.type = XBIT_comment;
    p->xbit.comment_chars = p->pbuf;
    Consume(p->pbuf);

    return 0;
}

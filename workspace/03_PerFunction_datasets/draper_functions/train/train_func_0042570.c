parse_markupdecl(Parser p)
{
    InputSource s;
    int c;
    int cur_line, cur_char;
    Entity cur_ent;

    if(p->state == PS_error)
	return error(p, "Attempt to continue reading DTD after error");

    clear_xbit(&p->xbit);

    require(skip_dtd_whitespace(p, 1));
    s = p->source;
    SourcePosition(s, &p->xbit.entity, &p->xbit.byte_offset);

    cur_ent = s->entity;
    cur_line = s->line_number;
    cur_char = s->next;

    c = get(s);
    switch(c)
    {
    case XEOE:
	p->xbit.type = XBIT_none;
	return 1;
    case '<':
	if(looking_at(p, "!ELEMENT"))
	{
	    require(expect_dtd_whitespace(p, "after ELEMENT"));
	    return parse_element_decl(p);
	}
	else if(looking_at(p, "!ATTLIST"))
	{
	    require(expect_dtd_whitespace(p, "after ATTLIST"));
	    return parse_attlist_decl(p);
	}
	else if(looking_at(p, "!ENTITY"))
	{
	    require(expect_dtd_whitespace(p, "after ENTITY"));
	    return parse_entity_decl(p, cur_ent, cur_line, cur_char);
	}
	else if(looking_at(p, "!NOTATION"))
	{
	    require(expect_dtd_whitespace(p, "after NOTATION"));
	    return parse_notation_decl(p);
	}
	else if(looking_at(p, "!["))
	    return parse_conditional(p);
	else if(looking_at(p, "?"))
	{
	    require(parse_pi(p));
	    if(p->dtd_callback)
		p->dtd_callback(&p->xbit, p->callback_arg);
	    else
		FreeXBit(&p->xbit);
	    return 0;
	}
	else if(looking_at(p, "!--"))
	{
	    if(ParserGetFlag(p, ReturnComments))
	    {
		require(parse_comment(p, 0));
		if(p->dtd_callback)
		    p->dtd_callback(&p->xbit, p->callback_arg);
		else
		    FreeXBit(&p->xbit);
		return 0;
	    }
	    else
		return parse_comment(p, 1);
	}
	else
	    return error(p, "Syntax error after < in dtd");
    default:
	unget(s);
	return error(p, "Expected \"<\" in dtd, but got %s", escape(c));
    }
}

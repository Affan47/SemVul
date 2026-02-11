parse_choice_or_seq_1(Parser p, int nchildren, char sep)
{
    ContentParticle cp = 0, cp1;
    int nsep = get(p->source);

    if(nsep == ')')
    {


	if(!(cp = Malloc(sizeof(*cp))) ||
	   !(cp->children = Malloc(nchildren * sizeof(cp))))
	{
	    Free(cp);
	    error(p, "System error");
	    return 0;
	}


	cp->type = sep == ',' ? CP_seq : CP_choice;
	cp->nchildren = nchildren;

	return cp;
    }

    if(nsep != '|' && nsep != ',')
    {
	error(p, "Expected | or , or ) in content declaration, got %s",
	      escape(nsep));
	return 0;
    }

    if(sep && nsep != sep)
    {
	error(p, "Content particle contains both | and ,");
	return 0;
    }

    require0(skip_dtd_whitespace(p, p->external_pe_depth > 0));

    if(!(cp1 = parse_cp(p)))
	return 0;

    require0(skip_dtd_whitespace(p, p->external_pe_depth > 0));

    if(!(cp = parse_choice_or_seq_1(p, nchildren+1, (char)nsep)))
	FreeContentParticle(cp1);
    else
	cp->children[nchildren] = cp1;

    return cp;
}

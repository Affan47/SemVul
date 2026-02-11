check_content_decl(Parser p, ContentParticle cp)
{
    int i;

    if(cp->type == CP_choice && cp->children[0]->type == CP_pcdata)
    {
	for(i=1; i<cp->nchildren; i++)
	    if(cp->children[i]->type != CP_name)
		return error(p, "Invalid mixed content declaration");

	if(cp->repetition != '*' &&
	   !(cp->nchildren == 1 && cp->repetition == 0))
	    return error(p, "Invalid mixed content declaration");

	return 0;
    }
    else
	return check_content_decl_1(p, cp);
}

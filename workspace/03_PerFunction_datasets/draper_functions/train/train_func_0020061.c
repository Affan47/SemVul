Response_response_checkall(char *name, rtype **_rt, resprec **_r)
{
	rtype	*rt;
	resprec	*r;

	for(rt=Response->rtypes; rt!=NULL; rt=rt->next)
		for(r=rt->responses; r!=NULL; r=r->next)
			if(isequal(r->name,name))
			{
				*_rt = rt;
				*_r = r;
				return r;
			}

	return NULL;
}

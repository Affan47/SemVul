con_accept(S5BConnection *c)
{
	Entry *e = findEntry(c);
	if(!e)
		return;

	if(e->c->d->req.fast) {
		if(targetShouldOfferProxy(e)) {
			queryProxy(e);
			return;
		}
	}
	entryContinue(e);
}

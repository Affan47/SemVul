subfrombill(obj, shkp)
register struct obj *obj;
register struct monst *shkp;
{
	register struct obj *otmp;

	sub_one_frombill(obj, shkp);

	if (Has_contents(obj))
	    for(otmp = obj->cobj; otmp; otmp = otmp->nobj) {
		if(otmp->oclass == COIN_CLASS) continue;

		if (Has_contents(otmp))
		    subfrombill(otmp, shkp);
		else
		    sub_one_frombill(otmp, shkp);
	    }
}

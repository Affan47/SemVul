artifact_exists(otmp, name, mod)
register struct obj *otmp;
register const char *name;
register boolean mod;
{
	register const struct artifact *a;

	if (otmp && *name)
	    for (a = artilist+1; a->otyp; a++)
		if (a->otyp == otmp->otyp && !strcmp(a->name, name)) {
		    register int m = a - artilist;
		    otmp->oartifact = (char)(mod ? m : 0);
		    otmp->age = 0;
		    if(otmp->otyp == RIN_INCREASE_DAMAGE)
			otmp->spe = 0;
		    artiexist[m] = mod;
		    break;
		}
	return;
}

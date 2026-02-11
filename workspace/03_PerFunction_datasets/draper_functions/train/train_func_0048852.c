canletgo(obj,word)
register struct obj *obj;
register const char *word;
{
	if(obj->owornmask & (W_ARMOR | W_RING | W_AMUL | W_TOOL)){
		if (*word)
			Norep("You cannot %s %s you are wearing.",word,
				something);
		return(FALSE);
	}
	if (obj->otyp == LOADSTONE && obj->cursed) {


		if (*word) {


			if (!strcmp(word, "throw") && obj->quan > 1L)
			    obj->corpsenm = 1;
			pline("For some reason, you cannot %s%s the stone%s!",
			      word, obj->corpsenm ? " any of" : "",
			      plur(obj->quan));
		}
		obj->corpsenm = 0;
		obj->bknown = 1;
		return(FALSE);
	}
	if (obj->otyp == LEASH && obj->leashmon != 0) {
		if (*word)
			pline_The("leash is tied around your %s.",
					body_part(HAND));
		return(FALSE);
	}
#ifdef STEED
	if (obj->owornmask & W_SADDLE) {
		if (*word)
			You("cannot %s %s you are sitting on.", word,
				something);
		return (FALSE);
	}
#endif
	return(TRUE);
}

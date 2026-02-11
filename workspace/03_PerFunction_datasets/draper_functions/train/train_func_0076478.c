use_cream_pie(obj)
struct obj *obj;
{
	boolean wasblind = Blind;
	boolean wascreamed = u.ucreamed;
	boolean several = FALSE;

	if (obj->quan > 1L) {
		several = TRUE;
		obj = splitobj(obj, 1L);
	}
	if (Hallucination)
		You("give yourself a facial.");
	else
		pline("You immerse your %s in %s%s.", body_part(FACE),
			several ? "one of " : "",
			several ? makeplural(the(xname(obj))) : the(xname(obj)));
	if(can_blnd((struct monst*)0, &youmonst, AT_WEAP, obj)) {
		int blindinc = rnd(25);
		u.ucreamed += blindinc;
		make_blinded(Blinded + (long)blindinc, FALSE);
		if (!Blind || (Blind && wasblind))
			pline("There's %ssticky goop all over your %s.",
				wascreamed ? "more " : "",
				body_part(FACE));
		else
			You_cant("see through all the sticky goop on your %s.",
				body_part(FACE));
	}
	if (obj->unpaid) {
		verbalize("You used it, you bought it!");
		bill_dummy_object(obj);
	}
	obj_extract_self(obj);
	delobj(obj);
	return(0);
}

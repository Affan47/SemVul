invocation_message(void)
{

	if(invocation_pos(u.ux, u.uy) && !On_stairs(u.ux, u.uy)) {
	    char buf[BUFSZ];
	    struct obj *otmp = carrying(CANDELABRUM_OF_INVOCATION);

	    nomul(0);
	    if (u.usteed) sprintf(buf, "beneath %s", y_monnam(u.usteed));
	    else
	    if (Levitation || Flying) strcpy(buf, "beneath you");
	    else sprintf(buf, "under your %s", makeplural(body_part(FOOT)));

	    You_feel("a strange vibration %s.", buf);
	    if (otmp && otmp->spe == 7 && otmp->lamplit)
		pline("%s %s!", The(xname(otmp)),
		    Blind ? "throbs palpably" : "glows with a strange light");
	}
}

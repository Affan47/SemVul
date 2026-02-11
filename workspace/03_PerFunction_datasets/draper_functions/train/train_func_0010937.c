Helmet_on()
{
    switch(uarmh->otyp) {
	case FEDORA:
	case HELMET:
	case DENTED_POT:
	case ELVEN_LEATHER_HELM:
	case DWARVISH_IRON_HELM:
	case ORCISH_HELM:
	case HELM_OF_TELEPATHY:
		break;
	case HELM_OF_BRILLIANCE:
		adj_abon(uarmh, uarmh->spe);
		break;
	case CORNUTHAUM:


		ABON(A_CHA) += (Role_if(PM_WIZARD) ? 1 : -1);
		flags.botl = 1;
		makeknown(uarmh->otyp);
		break;
	case HELM_OF_OPPOSITE_ALIGNMENT:
		if (u.ualign.type == A_NEUTRAL)
		    u.ualign.type = rn2(2) ? A_CHAOTIC : A_LAWFUL;
		else u.ualign.type = -(u.ualign.type);
		u.ublessed = 0;


	case DUNCE_CAP:
		if (!uarmh->cursed) {
		    if (Blind)
			pline("%s for a moment.", Tobjnam(uarmh, "vibrate"));
		    else
			pline("%s %s for a moment.",
			      Tobjnam(uarmh, "glow"), hcolor(NH_BLACK));
		    curse(uarmh);
		}
		flags.botl = 1;
		if (Hallucination) {
		    pline("My brain hurts!");
		} else if (uarmh->otyp == DUNCE_CAP) {
		    You_feel("%s.",
		  ACURR(A_INT) <= (ABASE(A_INT) + ABON(A_INT) + ATEMP(A_INT)) ?
			     "like sitting in a corner" : "giddy");
		} else {
		    Your("mind oscillates briefly.");
		    makeknown(HELM_OF_OPPOSITE_ALIGNMENT);
		}
		break;
	default: impossible(unknown_type, c_helmet, uarmh->otyp);
    }
    return 0;
}

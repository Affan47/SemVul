inside_gas_cloud(p1, p2)
genericptr_t p1;
genericptr_t p2;
{
    NhRegion *reg;
    struct monst *mtmp;
    int dam;

    reg = (NhRegion *) p1;
    dam = (int) reg->arg;
    if (p2 == NULL) {
	if (nonliving(youmonst.data) || Breathless)
	    return FALSE;
	if (!Blind)
	    make_blinded(1L, FALSE);
	if (!Poison_resistance) {
	    pline("%s is burning your %s!", Something, makeplural(body_part(LUNG)));
	    You("cough and spit blood!");
	    losehp(rnd(dam) + 5, "gas cloud", KILLED_BY_AN);
	    return FALSE;
	} else {
	    You("cough!");
	    return FALSE;
	}
    } else {
	mtmp = (struct monst *) p2;


	if (!nonliving(mtmp->data) && !breathless(mtmp->data)) {
	    if (cansee(mtmp->mx, mtmp->my))
		pline("%s coughs!", Monnam(mtmp));
	    setmangry(mtmp);
	    if (haseyes(mtmp->data) && mtmp->mcansee) {
		mtmp->mblinded = 1;
		mtmp->mcansee = 0;
	    }
	    if (resists_poison(mtmp))
		return FALSE;
	    mtmp->mhp -= rnd(dam) + 5;
	    if (mtmp->mhp <= 0) {
		if (heros_fault(reg))
		    killed(mtmp);
		else
		    monkilled(mtmp, "gas cloud", AD_DRST);
		if (mtmp->mhp <= 0) {
		    return TRUE;
		}
	    }
	}
    }
    return FALSE;
}

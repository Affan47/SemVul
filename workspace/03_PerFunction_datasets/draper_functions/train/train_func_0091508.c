passive_obj(mon, obj, mattk)
register struct monst *mon;
register struct obj *obj;
struct attack *mattk;
{
	register struct permonst *ptr = mon->data;
	register int i;


	if (!obj) {
	    obj = (u.twoweap && uswapwep && !rn2(2)) ? uswapwep : uwep;
	    if (!obj && mattk->adtyp == AD_ENCH)
		obj = uarmg;
	    if (!obj) return;
	}


	if (!mattk) {
	    for(i = 0; ; i++) {
		if(i >= NATTK) return;
		if(ptr->mattk[i].aatyp == AT_NONE) break;
	    }
	    mattk = &(ptr->mattk[i]);
	}

	switch(mattk->adtyp) {

	case AD_ACID:
	    if(!rn2(6)) {
		erode_obj(obj, TRUE, FALSE);
	    }
	    break;
	case AD_RUST:
	    if(!mon->mcan) {
		erode_obj(obj, FALSE, FALSE);
	    }
	    break;
	case AD_CORR:
	    if(!mon->mcan) {
		erode_obj(obj, TRUE, FALSE);
	    }
	    break;
	case AD_ENCH:
	    if (!mon->mcan) {
		if (drain_item(obj) && carried(obj) &&
		    (obj->known || obj->oclass == ARMOR_CLASS)) {
		    Your("%s less effective.", aobjnam(obj, "seem"));
	    	}
	    	break;
	    }
	  default:
	    break;
	}

	if (carried(obj)) update_inventory();
}

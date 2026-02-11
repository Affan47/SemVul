container_impact_dmg(obj)
struct obj *obj;
{
	struct monst *shkp;
	struct obj *otmp, *otmp2;
	long loss = 0L;
	boolean costly, insider;
	xchar x = obj->ox, y = obj->oy;


	if (!Is_container(obj) || Is_mbag(obj)) return;

	costly = ((shkp = shop_keeper(*in_rooms(x, y, SHOPBASE))) &&
		  costly_spot(x, y));
	insider = (*u.ushops && inside_shop(u.ux, u.uy) &&
		   *in_rooms(x, y, SHOPBASE) == *u.ushops);

	for (otmp = obj->cobj; otmp; otmp = otmp2) {
	    const char *result = (char *)0;

	    otmp2 = otmp->nobj;
	    if (objects[otmp->otyp].oc_material == GLASS &&
		otmp->oclass != GEM_CLASS && !obj_resists(otmp, 33, 100)) {
		result = "shatter";
	    } else if (otmp->otyp == EGG && !rn2(3)) {
		result = "cracking";
	    }
	    if (result) {
		if (otmp->otyp == MIRROR) change_luck(-2);


		if (otmp->otyp == EGG && otmp->spe && otmp->corpsenm >= LOW_PM)
		    change_luck(-1);
		You_hear("a muffled %s.", result);
		if (costly)
		    loss += stolen_value(otmp, x, y,
					 (boolean)shkp->mpeaceful, TRUE);
		if (otmp->quan > 1L)
		    useup(otmp);
		else {
		    obj_extract_self(otmp);
		    obfree(otmp, (struct obj *) 0);
		}
	    }
	}
	if (costly && loss) {
	    if (!insider) {
		You("caused %ld %s worth of damage!", loss, currency(loss));
		make_angry_shk(shkp, x, y);
	    } else {
		You("owe %s %ld %s for objects destroyed.",
		    mon_nam(shkp), loss, currency(loss));
	    }
	}
}

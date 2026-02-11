burnarmor(victim)
struct monst *victim;
{
    struct obj *item;
    char buf[BUFSZ];
    int mat_idx;

    if (!victim) return 0;
#define burn_dmg(obj,descr) rust_dmg(obj, descr, 0, FALSE, victim)
    while (1) {
	switch (rn2(5)) {
	case 0:
	    item = (victim == &youmonst) ? uarmh : which_armor(victim, W_ARMH);
	    if (item) {
		mat_idx = objects[item->otyp].oc_material;
	    	Sprintf(buf,"%s helmet", materialnm[mat_idx] );
	    }
	    if (!burn_dmg(item, item ? buf : "helmet")) continue;
	    break;
	case 1:
	    item = (victim == &youmonst) ? uarmc : which_armor(victim, W_ARMC);
	    if (item) {
		(void) burn_dmg(item, cloak_simple_name(item));
		return TRUE;
	    }
	    item = (victim == &youmonst) ? uarm : which_armor(victim, W_ARM);
	    if (item) {
		(void) burn_dmg(item, xname(item));
		return TRUE;
	    }
#ifdef TOURIST
	    item = (victim == &youmonst) ? uarmu : which_armor(victim, W_ARMU);
	    if (item)
		(void) burn_dmg(item, "shirt");
#endif
	    return TRUE;
	case 2:
	    item = (victim == &youmonst) ? uarms : which_armor(victim, W_ARMS);
	    if (!burn_dmg(item, "wooden shield")) continue;
	    break;
	case 3:
	    item = (victim == &youmonst) ? uarmg : which_armor(victim, W_ARMG);
	    if (!burn_dmg(item, "gloves")) continue;
	    break;
	case 4:
	    item = (victim == &youmonst) ? uarmf : which_armor(victim, W_ARMF);
	    if (!burn_dmg(item, "boots")) continue;
	    break;
	}
	break;
    }
    return FALSE;
#undef burn_dmg
}

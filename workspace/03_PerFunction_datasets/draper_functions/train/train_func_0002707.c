choke(food)
	register struct obj *food;
{

	if (u.uhs != SATIATED) {
		if (!food || food->otyp != AMULET_OF_STRANGULATION)
			return;
	} else if (Role_if(PM_KNIGHT) && u.ualign.type == A_LAWFUL) {
			adjalign(-1);
			You_feel("like a glutton!");
	}

	exercise(A_CON, FALSE);

	if (Breathless || (!Strangled && !rn2(20))) {

		if (food && food->otyp == AMULET_OF_STRANGULATION) {
			You("choke, but recover your composure.");
			return;
		}
		You("stuff yourself and then vomit voluminously.");
		morehungry(1000);
		nomovemsg = 0;
		vomit();
	} else {
		killer_format = KILLED_BY_AN;


		if(food) {
			You("choke over your %s.", foodword(food));
			if (food->oclass == COIN_CLASS) {
				killer = "a very rich meal";
			} else {
				killer = food_xname(food, FALSE);
				if (food->otyp == CORPSE &&
				    (mons[food->corpsenm].geno & G_UNIQ)) {
				    if (!type_is_pname(&mons[food->corpsenm]))
					killer = the(killer);
				    killer_format = KILLED_BY;
				}
			}
		} else {
			You("choke over it.");
			killer = "quick snack";
		}
		You("die...");
		done(CHOKING);
	}
}

GetWMonTar(ARegion *r, int tarnum, Unit *mon) {
	forlist(&r->objects) {
		Object *o = (Object *) elem;
		forlist(&o->units) {
			Unit *u = (Unit *) elem;
			if (u->type == U_NORMAL || u->type == U_MAGE ||
					u->type == U_APPRENTICE) {
				if (mon->CanSee(r, u) && mon->CanCatch(r, u)) {
					int num = u->GetMen();
					if (num && tarnum < num) return u;
					tarnum -= num;
				}
			}
		}
	}
	return 0;
}

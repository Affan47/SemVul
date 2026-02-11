Do1Quit(Faction *f)
{
	forlist(&regions) {
		ARegion *r = (ARegion *) elem;
		forlist(&r->objects) {
			Object *o = (Object *) elem;
			forlist(&o->units) {
				Unit *u = (Unit *) elem;
				if (u->faction == f) {
					o->units.Remove(u);
					delete u;
				}
			}
		}
	}
}

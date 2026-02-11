GetAFacs(ARegion *r, Unit *att, Unit *tar, AList &dfacs,
		AList &afacs, AList &atts)
{
	forlist((&r->objects)) {
		Object * obj = (Object *) elem;
		forlist((&obj->units)) {
			Unit * u = (Unit *) elem;
			if (u->canattack && u->IsAlive()) {
				int add = 0;
				if ((u->faction == att->faction ||
							u->GetAttitude(r,tar) == A_HOSTILE) &&
						(u->guard != GUARD_AVOID || u == att)) {
					add = 1;
				} else {
					if (u->guard == GUARD_ADVANCE &&
							u->GetAttitude(r,tar) != A_ALLY) {
						add = 1;
					} else {
						if (u->attackorders) {
							forlist(&(u->attackorders->targets)) {
								UnitId * id = (UnitId *) elem;
								Unit *t = r->GetUnitId(id, u->faction->num);
								if (!t) continue;
								if (t == tar) {
									u->attackorders->targets.Remove(id);
									delete id;
								}
								if(t->faction == tar->faction) add = 1;
							}
						}
					}
				}

				if (add) {
					if (!GetFaction2(&dfacs,u->faction->num)) {
						Location * l = new Location;
						l->unit = u;
						l->obj = obj;
						l->region = r;
						atts.Add(l);
						if (!GetFaction2(&afacs,u->faction->num)) {
							FactionPtr * p = new FactionPtr;
							p->ptr = u->faction;
							afacs.Add(p);
						}
					}
				}
			}
		}
	}
}

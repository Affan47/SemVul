DoAutoAttack(ARegion *r, Unit *u) {
  forlist(&r->objects) {
	Object *o = (Object *) elem;
	forlist(&o->units) {
	  Unit *t = (Unit *) elem;
	  if (u->guard != GUARD_AVOID && (u->GetAttitude(r, t) == A_HOSTILE)) {
	AttemptAttack(r, u, t, 1);
	  }
	  if (u->canattack == 0 || u->IsAlive() == 0)
	return;
	}
  }
}

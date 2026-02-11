Forbids(ARegion *r, Unit *u)
{
	if (guard != GUARD_GUARD) return 0;
	if (!IsAlive()) return 0;
	if (!CanSee(r, u, Globals->SKILL_PRACTICE_AMOUNT > 0)) return 0;
	if (!CanCatch(r, u)) return 0;
	if (GetAttitude(r, u) < A_NEUTRAL) return 1;
	return 0;
}

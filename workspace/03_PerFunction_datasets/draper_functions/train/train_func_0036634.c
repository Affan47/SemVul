hitfloor(obj)
register struct obj *obj;
{
	if (IS_SOFT(levl[u.ux][u.uy].typ) || u.uinwater) {
		dropy(obj);
		return;
	}
	if (IS_ALTAR(levl[u.ux][u.uy].typ))
		doaltarobj(obj);
	else
		pline("%s hit%s the %s.", Doname2(obj),
		      (obj->quan == 1L) ? "s" : "", surface(u.ux,u.uy));

	if (hero_breaks(obj, u.ux, u.uy, TRUE)) return;
	if (ship_object(obj, u.ux, u.uy, FALSE)) return;
	dropy(obj);
	if (!u.uswallow) container_impact_dmg(obj);
}

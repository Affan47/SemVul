does_block(x,y,lev)
    int x, y;
    register struct rm    *lev;
{
    struct obj   *obj;
    struct monst *mon;


    if (IS_ROCK(lev->typ) || lev->typ == TREE || (IS_DOOR(lev->typ) &&
			    (lev->doormask & (D_CLOSED|D_LOCKED|D_TRAPPED) )))
	return 1;

    if (lev->typ == CLOUD || lev->typ == WATER ||
			(lev->typ == MOAT && Underwater))
	return 1;


    for (obj = level.objects[x][y]; obj; obj = obj->nexthere)
	if (obj->otyp == BOULDER) return 1;


    if ((mon = m_at(x,y)) && (!mon->minvis || See_invisible) &&
	  ((mon->m_ap_type == M_AP_FURNITURE &&
	  (mon->mappearance == S_hcdoor || mon->mappearance == S_vcdoor)) ||
	  (mon->m_ap_type == M_AP_OBJECT && mon->mappearance == BOULDER)))
	return 1;

    return 0;
}

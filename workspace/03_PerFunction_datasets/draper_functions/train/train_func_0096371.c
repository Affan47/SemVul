blocked_boulder(dx,dy)
int dx,dy;
{
    register struct obj *otmp;
    long count = 0L;

    for(otmp = level.objects[u.ux+dx][u.uy+dy]; otmp; otmp = otmp->nexthere) {
	if(otmp->otyp == BOULDER)
	    count += otmp->quan;
    }

    switch(count) {
	case 0: return FALSE;
	case 1: break;
	default: return TRUE;

    }

    if (!isok(u.ux+2*dx, u.uy+2*dy))
	return TRUE;
    if (IS_ROCK(levl[u.ux+2*dx][u.uy+2*dy].typ))
	return TRUE;
    if (sobj_at(BOULDER, u.ux+2*dx, u.uy+2*dy))
	return TRUE;

    return FALSE;
}

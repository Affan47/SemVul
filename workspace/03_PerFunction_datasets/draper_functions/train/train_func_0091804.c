mbag_explodes(obj, depthin)
    struct obj *obj;
    int depthin;
{

    if ((obj->otyp == WAN_CANCELLATION || obj->otyp == BAG_OF_TRICKS) &&
	    obj->spe <= 0)
	return FALSE;


    if ((Is_mbag(obj) || obj->otyp == WAN_CANCELLATION) &&
	(rn2(1 << (depthin > 7 ? 7 : depthin)) <= depthin))
	return TRUE;
    else if (Has_contents(obj)) {
	struct obj *otmp;

	for (otmp = obj->cobj; otmp; otmp = otmp->nobj)
	    if (mbag_explodes(otmp, depthin+1)) return TRUE;
    }
    return FALSE;
}

snuff_lit(obj)
struct obj *obj;
{
	xchar x, y;

	if (obj->lamplit) {
	    if (obj->otyp == OIL_LAMP || obj->otyp == MAGIC_LAMP ||
		    obj->otyp == BRASS_LANTERN || obj->otyp == POT_OIL) {
		(void) get_obj_location(obj, &x, &y, 0);
		if (obj->where == OBJ_MINVENT ? cansee(x,y) : !Blind)
		    pline("%s %s out!", Yname2(obj), otense(obj, "go"));
		end_burn(obj, TRUE);
		return TRUE;
	    }
	    if (snuff_candle(obj)) return TRUE;
	}
	return FALSE;
}

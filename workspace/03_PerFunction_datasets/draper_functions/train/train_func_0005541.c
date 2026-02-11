weffects(obj)
register struct	obj	*obj;
{
	int otyp = obj->otyp;
	boolean disclose = FALSE, was_unkn = !objects[otyp].oc_name_known;

	exercise(A_WIS, TRUE);
#ifdef STEED
	if (u.usteed && (objects[otyp].oc_dir != NODIR) &&
	    !u.dx && !u.dy && (u.dz > 0) && zap_steed(obj)) {
		disclose = TRUE;
	} else
#endif
	if (objects[otyp].oc_dir == IMMEDIATE) {
	    obj_zapped = FALSE;

	    if (u.uswallow) {
		(void) bhitm(u.ustuck, obj);

	    } else if (u.dz) {
		disclose = zap_updown(obj);
	    } else {
		(void) bhit(u.dx,u.dy, rn1(8,6),ZAPPED_WAND, bhitm,bhito, obj);
	    }

	    if (obj_zapped)
		You_feel("shuddering vibrations.");

	} else if (objects[otyp].oc_dir == NODIR) {
	    zapnodir(obj);

	} else {


	    if (otyp == WAN_DRILLING || otyp == SPE_DRILLING)
		zap_dig();
            else if (otyp == WAN_CONSTRUCT)
	    	zap_construct();
	    else if (otyp >= SPE_MAGIC_MISSILE && otyp <= SPE_BUSTER_BEAM)
		buzz(otyp - SPE_MAGIC_MISSILE + 10,
		     u.ulevel / 2 + 1,
		     u.ux, u.uy, u.dx, u.dy);
	    else if (otyp >= WAN_MAGIC_MISSILE && otyp <= WAN_LIGHTNING)
		buzz(otyp - WAN_MAGIC_MISSILE,
		     (otyp == WAN_MAGIC_MISSILE) ? 2 : 6,
		     u.ux, u.uy, u.dx, u.dy);
	    else
		impossible("weffects: unexpected spell or wand");
	    disclose = TRUE;
	}
	if (disclose && was_unkn) {
	    makeknown(otyp);
	    more_experienced(0,10);
	}
	return;
}

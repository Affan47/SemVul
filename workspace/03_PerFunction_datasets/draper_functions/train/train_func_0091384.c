loot_mon(mtmp, passed_info, prev_loot)
struct monst *mtmp;
int *passed_info;
boolean *prev_loot;
{
    int c = -1;
    int timepassed = 0;
#ifdef STEED
    struct obj *otmp;
    char qbuf[QBUFSZ];


    if (mtmp && mtmp != u.usteed && (otmp = which_armor(mtmp, W_SADDLE))) {
	long unwornmask;
	if (passed_info) *passed_info = 1;
	Sprintf(qbuf, "Do you want to remove the saddle from %s?",
		x_monnam(mtmp, ARTICLE_THE, (char *)0, SUPPRESS_SADDLE, FALSE));
	if ((c = yn_function(qbuf, ynqchars, 'n')) == 'y') {
		if (nolimbs(youmonst.data)) {
		    You_cant("do that without limbs.");
		    return (0);
		}
		if (otmp->cursed) {
		    You("can't. The saddle seems to be stuck to %s.",
			x_monnam(mtmp, ARTICLE_THE, (char *)0,
				SUPPRESS_SADDLE, FALSE));


			return (1);
		}
		obj_extract_self(otmp);
		if ((unwornmask = otmp->owornmask) != 0L) {
		    mtmp->misc_worn_check &= ~unwornmask;
		    otmp->owornmask = 0L;
		    update_mon_intrinsics(mtmp, otmp, FALSE, FALSE);
		}
		otmp = hold_another_object(otmp, "You drop %s!", doname(otmp),
					(const char *)0);
		timepassed = rnd(3);
		if (prev_loot) *prev_loot = TRUE;
	} else if (c == 'q') {
		return (0);
	}
    }
#endif

    if (u.uswallow) {
	int count = passed_info ? *passed_info : 0;
	timepassed = pickup(count);
    }
    return timepassed;
}

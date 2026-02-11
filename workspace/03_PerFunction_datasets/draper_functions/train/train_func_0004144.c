steal_it(mdef, mattk)
struct monst *mdef;
struct attack *mattk;
{
	struct obj *otmp, *stealoid, **minvent_ptr;
	long unwornmask;

	if (!mdef->minvent) return;


	stealoid = (struct obj *)0;
	if (could_seduce(&youmonst, mdef, mattk)) {

	    minvent_ptr = &mdef->minvent;
	    while ((otmp = *minvent_ptr) != 0)
		if (otmp->owornmask & W_ARM) {
		    if (stealoid) panic("steal_it: multiple worn suits");
		    *minvent_ptr = otmp->nobj;
		    stealoid = otmp;
		    stealoid->nobj = (struct obj *)0;
		} else {
		    minvent_ptr = &otmp->nobj;
		}
	    *minvent_ptr = stealoid;
	}

	if (stealoid) {
	    if (gender(mdef) == (int) u.mfemale &&
			youmonst.data->mlet == S_NYMPH)
		You("charm %s.  She gladly hands over her possessions.",
		    mon_nam(mdef));
	    else
		You("seduce %s and %s starts to take off %s clothes.",
		    mon_nam(mdef), mhe(mdef), mhis(mdef));
	}

	while ((otmp = mdef->minvent) != 0) {
	    if (!Upolyd) break;

	    obj_extract_self(otmp);
	    if ((unwornmask = otmp->owornmask) != 0L) {
		mdef->misc_worn_check &= ~unwornmask;
		if (otmp->owornmask & W_WEP) {
		    setmnotwielded(mdef,otmp);
		    MON_NOWEP(mdef);
		}
		otmp->owornmask = 0L;
		update_mon_intrinsics(mdef, otmp, FALSE, FALSE);

		if (otmp == stealoid)
		    pline("%s finishes taking off %s suit.",
			  Monnam(mdef), mhis(mdef));
	    }

	    otmp = hold_another_object(otmp, "You snatched but dropped %s.",
				       doname(otmp), "You steal: ");
	    if (otmp->where != OBJ_INVENT) continue;
	    if (otmp->otyp == CORPSE &&
		    touch_petrifies(&mons[otmp->corpsenm]) && !uarmg) {
		char kbuf[BUFSZ];

		Sprintf(kbuf, "stolen %s corpse", mons[otmp->corpsenm].mname);
		instapetrify(kbuf);
		break;
	    }

	    if (unwornmask & W_WEP) {
		possibly_unwield(mdef, FALSE);
	    } else if (unwornmask & W_ARMG) {
		mselftouch(mdef, (const char *)0, TRUE);
		if (mdef->mhp <= 0)
		    return;
	    }

	    if (!stealoid) break;
	}
}

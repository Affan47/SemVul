mrustm(magr, mdef, obj)
register struct monst *magr, *mdef;
register struct obj *obj;
{
	boolean is_acid;

	if (!magr || !mdef || !obj) return;

	if (dmgtype(mdef->data, AD_CORR))
	    is_acid = TRUE;
	else if (dmgtype(mdef->data, AD_RUST))
	    is_acid = FALSE;
	else
	    return;

	if (!mdef->mcan &&
	    (is_acid ? is_corrodeable(obj) : is_rustprone(obj)) &&
	    (is_acid ? obj->oeroded2 : obj->oeroded) < MAX_ERODE) {
		if (obj->greased || obj->oerodeproof || (obj->blessed && rn2(3))) {
		    if (cansee(mdef->mx, mdef->my) && flags.verbose)
			pline("%s weapon is not affected.",
			                 s_suffix(Monnam(magr)));
		    if (obj->greased && !rn2(2)) obj->greased = 0;
		} else {
		    if (cansee(mdef->mx, mdef->my)) {
			pline("%s %s%s!", s_suffix(Monnam(magr)),
			    aobjnam(obj, (is_acid ? "corrode" : "rust")),
			    (is_acid ? obj->oeroded2 : obj->oeroded)
				? " further" : "");
		    }
		    if (is_acid) obj->oeroded2++;
		    else obj->oeroded++;
		}
	}
}

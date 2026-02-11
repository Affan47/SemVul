buzzmu(struct monst *mtmp, struct attack *mattk)
{


	if (mattk->adtyp > AD_SPC2)
	    return(0);

	if (mtmp->mcan) {
	    cursetxt(mtmp, false);
	    return(0);
	}
	if(lined_up(mtmp) && rn2(3)) {
	    nomul(0);
	    if(mattk->adtyp && (mattk->adtyp < 11)) {
		if(canseemon(mtmp))
		    pline("%s zaps you with a %s!", Monnam(mtmp),
			  flash_types[ad_to_typ(mattk->adtyp)]);
		buzz(-ad_to_typ(mattk->adtyp), (int)mattk->damn,
		     mtmp->mx, mtmp->my, sgn(tbx), sgn(tby));
	    } else impossible("Monster spell %d cast", mattk->adtyp-1);
	}
	return(1);
}

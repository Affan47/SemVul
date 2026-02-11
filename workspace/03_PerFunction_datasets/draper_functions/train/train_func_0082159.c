final_level()
{
	struct monst *mtmp;
	struct obj *otmp;
	coord mm;
	int i;


	for (mtmp = fmon; mtmp; mtmp = mtmp->nmon)
	    if (!DEADMONSTER(mtmp)) reset_hostility(mtmp);


	create_mplayers(rn1(4, 3), TRUE);


	if (Conflict) {
	    pline(
	     "A voice booms: \"Thy desire for conflict shall be fulfilled!\"");
	    for (i = rnd(4); i > 0; --i) {
		mm.x = u.ux;
		mm.y = u.uy;
		if (enexto(&mm, mm.x, mm.y, &mons[PM_ANGEL]))
		    (void) mk_roamer(&mons[PM_ANGEL], u.ualign.type,
				     mm.x, mm.y, FALSE);
	    }

	} else if (u.ualign.record > 8) {
	    pline("A voice whispers: \"Thou hast been worthy of me!\"");
	    mm.x = u.ux;
	    mm.y = u.uy;
	    if (enexto(&mm, mm.x, mm.y, &mons[PM_ANGEL])) {
		if ((mtmp = mk_roamer(&mons[PM_ANGEL], u.ualign.type,
				      mm.x, mm.y, TRUE)) != 0) {
		    if (!Blind)
			pline("An angel appears near you.");
		    else
			You_feel("the presence of a friendly angel near you.");


		    mtmp->mtame = 10;

		    mtmp->m_lev = rn1(8,15);
		    mtmp->mhp = mtmp->mhpmax =
					d((int)mtmp->m_lev,10) + 30 + rnd(30);
		    if ((otmp = select_hwep(mtmp)) == 0) {
			otmp = mksobj(SILVER_SABER, FALSE, FALSE);
			if (mpickobj(mtmp, otmp))
			    panic("merged weapon?");
		    }
		    bless(otmp);
		    if (otmp->spe < 4) otmp->spe += rnd(4);
		    if ((otmp = which_armor(mtmp, W_ARMS)) == 0 ||
			    otmp->otyp != SHIELD_OF_REFLECTION) {
			(void) mongets(mtmp, AMULET_OF_REFLECTION);
			m_dowear(mtmp, TRUE);
		    }
		}
	    }
	}
}

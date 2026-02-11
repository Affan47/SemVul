fprefx(otmp)
struct obj *otmp;
{
	switch(otmp->otyp) {
	    case FOOD_RATION:
		if(u.uhunger <= 200)
		    pline(Hallucination ? "Oh wow, like, superior, man!" :
			  "That food really hit the spot!");
		else if(u.uhunger <= 700) pline("That satiated your %s!",
						body_part(STOMACH));
		break;
	    case TRIPE_RATION:
		if (carnivorous(youmonst.data) && !humanoid(youmonst.data))
		    pline("That tripe ration was surprisingly good!");
		else if (maybe_polyd(is_orc(youmonst.data), Race_if(PM_ORC)))
		    pline(Hallucination ? "Tastes great! Less filling!" :
			  "Mmm, tripe... not bad!");
		else {
		    pline("Yak - dog food!");
		    more_experienced(1,0);
		    newexplevel();


		    if (rn2(2) && !CANNIBAL_ALLOWED())
			make_vomiting((long)rn1(victual.reqtime, 14), FALSE);
		}
		break;
	    case GOOSE_POOP:
		pline("This %s is disgusting! You strange thing!",
				singular(otmp, xname));
		make_vomiting((long)rn1(victual.reqtime, 5), FALSE);
		break;
	    case MONKEY_HEAD:
		if (Role_if(PM_ARCHEOLOGIST)) {
		    pline("Aah, dessert! Chilled monkey brains.");
		    break;
		}
	    case PLACENTA:
	    case MEATBALL:
	    case MEAT_STICK:
	    case HUGE_CHUNK_OF_MEAT:
	    case MEAT_RING:
		goto give_feedback;

	    case CLOVE_OF_GARLIC:
		if (is_undead(youmonst.data)) {
			make_vomiting((long)rn1(victual.reqtime, 5), FALSE);
			break;
		}

	    default:
		if (otmp->otyp==SLIME_MOLD && !otmp->cursed
			&& otmp->spe == current_fruit)
		    pline("My, that was a %s %s!",
			  Hallucination ? "primo" : "yummy",
			  singular(otmp, xname));
		else
#ifdef UNIX
		if (otmp->otyp == APPLE || otmp->otyp == PEAR) {
		    if (!Hallucination) pline("Core dumped.");
		    else {

			int x = rnd(100);
			if (x <= 75)
			    pline("Segmentation fault -- core dumped.");
			else if (x <= 99)
			    pline("Bus error -- core dumped.");
			else pline("Yo' mama -- core dumped.");
		    }
		} else
#endif
#ifdef MAC
		if (otmp->otyp == APPLE) {
			pline("Delicious!  Must be a Macintosh!");
		} else
#endif
		if (otmp->otyp == EGG && stale_egg(otmp)) {
		    pline("Ugh.  Rotten egg.");
		    make_vomiting(Vomiting+d(10,4), TRUE);
		} else
 give_feedback:
		    pline("This %s is %s", singular(otmp, xname),
		      otmp->cursed ? (Hallucination ? "grody!" : "terrible!") :
		      (otmp->otyp == CRAM_RATION
		      || otmp->otyp == K_RATION
		      || otmp->otyp == C_RATION)
		      ? "bland." :
		      Hallucination ? "gnarly!" : "delicious!");
		break;
	}
}

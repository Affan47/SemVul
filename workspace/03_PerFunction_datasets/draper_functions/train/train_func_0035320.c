take_off(void)
{
	int i;
	struct obj *otmp;

	if (taking_off) {
	    if (todelay > 0) {
		todelay--;
		return(1);
	    } else {
		if ((otmp = do_takeoff())) off_msg(otmp);
	    }
	    takeoff_mask &= ~taking_off;
	    taking_off = 0L;
	}

	for(i = 0; takeoff_order[i]; i++)
	    if(takeoff_mask & takeoff_order[i]) {
		taking_off = takeoff_order[i];
		break;
	    }

	otmp = (struct obj *) 0;
	todelay = 0;

	if (taking_off == 0L) {
	  You("finish %s.", disrobing);
	  return 0;
	} else if (taking_off == W_WEP) {
	  todelay = 1;
	} else if (taking_off == W_SWAPWEP) {
	  todelay = 1;
	} else if (taking_off == W_QUIVER) {
	  todelay = 1;
	} else if (taking_off == WORN_ARMOR) {
	  otmp = uarm;


	  if (uarmc) todelay += 2 * objects[uarmc->otyp].oc_delay + 1;
	} else if (taking_off == WORN_CLOAK) {
	  otmp = uarmc;
	} else if (taking_off == WORN_BOOTS) {
	  otmp = uarmf;
	} else if (taking_off == WORN_GLOVES) {
	  otmp = uarmg;
	} else if (taking_off == WORN_HELMET) {
	  otmp = uarmh;
	} else if (taking_off == WORN_SHIELD) {
	  otmp = uarms;
	} else if (taking_off == WORN_SHIRT) {
	  otmp = uarmu;

	  if (uarm)  todelay += 2 * objects[uarm->otyp].oc_delay;
	  if (uarmc) todelay += 2 * objects[uarmc->otyp].oc_delay + 1;
	} else if (taking_off == WORN_AMUL) {
	  todelay = 1;
	} else if (taking_off == LEFT_RING) {
	  todelay = 1;
	} else if (taking_off == RIGHT_RING) {
	  todelay = 1;
	} else if (taking_off == WORN_BLINDF) {
	  todelay = 2;
	} else {
	  impossible("take_off: taking off %lx", taking_off);
	  return 0;
	}

	if (otmp) todelay += objects[otmp->otyp].oc_delay;


	if (todelay > 0) todelay--;

	set_occupation(take_off, disrobing, 0);
	return(1);
}

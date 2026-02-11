doremring(void)
{
	struct obj *otmp = 0;
	int Accessories = 0;

#define MOREACC(x) if (x) { Accessories++; otmp = x; }
	MOREACC(uleft);
	MOREACC(uright);
	MOREACC(uamul);
	MOREACC(ublindf);

	if(!Accessories) {
		pline("Not wearing any accessories.%s", (iflags.cmdassist &&
			    (uarm || uarmc || uarmu ||
			     uarms || uarmh || uarmg || uarmf)) ?
		      "  Use 'T' command to take off armor." : "");
		return(0);
	}
	if (Accessories != 1) otmp = getobj(accessories, "remove");
	if(!otmp) return(0);
	if(!(otmp->owornmask & (W_RING | W_AMUL | W_TOOL))) {
		You("are not wearing that.");
		return(0);
	}

	reset_remarm();
	select_off(otmp);
	if (!takeoff_mask) return 0;
	reset_remarm();

	if (otmp == uright || otmp == uleft) {


		off_msg(otmp);
		Ring_off(otmp);
	} else if (otmp == uamul) {
		Amulet_off();
		off_msg(otmp);
	} else if (otmp == ublindf) {
		Blindf_off(otmp);
	} else {
		impossible("removing strange accessory?");
	}
	return(1);
}

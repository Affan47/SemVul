ivopen()
{
	if(here(CLAM))
		object=CLAM;
	if(here(OYSTER))
		object=OYSTER;
	if(at(DOOR))
		object=DOOR;
	if(at(GRATE))
		object=GRATE;
	if(here(CHAIN)) {
		if(object != 0) {
			needobj();
			return;
		}
		object=CHAIN;
	}
	if(object==0) {
		rspeak(28);
		return;
	}
	vopen();
}

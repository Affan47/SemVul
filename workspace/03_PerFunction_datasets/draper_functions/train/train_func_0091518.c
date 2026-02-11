addinv_core1(obj)
struct obj *obj;
{
	if (obj->oclass == COIN_CLASS) {
#ifndef GOLDOBJ
		u.ugold += obj->quan;
#else
		flags.botl = 1;
#endif
	} else if (obj->otyp == AMULET_OF_YENDOR) {
		if (u.uhave.amulet) impossible("already have amulet?");
		u.uhave.amulet = 1;
	} else if (obj->otyp == CANDELABRUM_OF_INVOCATION) {
		if (u.uhave.menorah) impossible("already have candelabrum?");
		u.uhave.menorah = 1;
	} else if (obj->otyp == BELL_OF_OPENING) {
		if (u.uhave.bell) impossible("already have silver bell?");
		u.uhave.bell = 1;
	} else if (obj->otyp == CLAPPER_OF_OPENING) {
		if (u.uhave.clapper) impossible("already have clapper?");
		u.uhave.clapper = 1;
	} else if (obj->otyp == SPE_BOOK_OF_THE_DESU) {
		if (u.uhave.book) impossible("already have the book?");
		u.uhave.book = 1;
	} else if (obj->oartifact) {
		if (is_quest_artifact(obj)) {
		    if (u.uhave.questart)
			impossible("already have quest artifact?");
		    u.uhave.questart = 1;
		    artitouch();
		}
		set_artifact_intrinsic(obj, 1, W_ART);
	}
}

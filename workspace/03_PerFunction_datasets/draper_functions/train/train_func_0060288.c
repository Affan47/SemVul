lantern_message(obj)
struct obj *obj;
{

	switch (obj->where) {
	    case OBJ_INVENT:
		Your("lantern is getting dim.");
		if (Hallucination)
		    pline("Batteries have not been invented yet.");
		break;
	    case OBJ_FLOOR:
		You("see a lantern getting dim.");
		break;
	    case OBJ_MINVENT:
		pline("%s lantern is getting dim.",
		    s_suffix(Monnam(obj->ocarry)));
		break;
	}
}

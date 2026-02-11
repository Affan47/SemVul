deriveIx(t)
Tycon t; {
    if (isEnumType(t)) {
	return cons(mkBind("range",mkVarAlts(tycon(t).line,nameEnRange)),
		cons(mkBind("index",mkVarAlts(tycon(t).line,nameEnIndex)),
		 cons(mkBind("inRange",mkVarAlts(tycon(t).line,nameEnInRng)),
		  NIL)));
    } else if (isTuple(t)) {
	return mkIxBinds(0,t,tupleOf(t));
    } else if (isTycon(t) && cfunOf(hd(tycon(t).defn))==0) {
	return mkIxBinds(tycon(t).line,
			 hd(tycon(t).defn),
			 userArity(hd(tycon(t).defn)));
    }

    ERRMSG(tycon(t).line)
	"Can only derive instances of Ix for enumeration or product types"
    EEND;
    return NIL;
}

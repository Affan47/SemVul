extractFixdecls(es)
List es; {
    List fixdecls = NIL;

    for(; nonNull(es); es=tl(es)) {
	if (fst(hd(es))==FIXDECL) {
	    fixdecls = cons(snd(hd(es)),fixdecls);
	}
    }
    return fixdecls;
}

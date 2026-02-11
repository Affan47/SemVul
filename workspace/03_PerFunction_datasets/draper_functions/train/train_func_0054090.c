addMembers(c)
Class c; {
    List ms  = fst(cclass(c).members);
    List fs  = snd(cclass(c).members);
    List ns  = NIL;
    Int  mno;

    for (mno=0; mno<cclass(c).numSupers; mno++) {
	ns = cons(newDSel(c,mno),ns);
    }
    cclass(c).dsels = rev(ns);

    for (mno=1, ns=NIL; nonNull(ms); ms=tl(ms)) {
	Int  line = intOf(fst3(hd(ms)));
	List vs   = rev(snd3(hd(ms)));
	Type t    = thd3(hd(ms));
	for (; nonNull(vs); vs=tl(vs)) {
	    ns = cons(newMember(line,mno++,hd(vs),t,c),ns);
	}
    }
    cclass(c).members    = rev(ns);
    cclass(c).numMembers = length(cclass(c).members);

    for (; nonNull(fs); fs=tl(fs)) {
	Int    line = intOf(fst3(hd(fs)));
	List   ops  = snd3(hd(fs));
	Syntax s    = intOf(thd3(hd(fs)));
	for (; nonNull(ops); ops=tl(ops)) {
	    Name n = nameIsMember(textOf(hd(ops)),cclass(c).members);
	    if (isNull(n)) {
		missFixity(line,textOf(hd(ops)));
	    } else if (name(n).syntax!=NO_SYNTAX) {
		dupFixity(line,textOf(hd(ops)));
	    }
	    name(n).syntax = s;
	}
    }


    mno		       = cclass(c).numSupers + cclass(c).numMembers;
    cclass(c).dcon     = addPrimCfun(generateText("Make.%s",c),mno,0,NIL);
    if (mno==1)	{
	name(cclass(c).dcon).defn = nameId;
	if (nonNull(cclass(c).members)) {
	    name(hd(cclass(c).members)).number = mfunNo(0);
	}
    }
    cclass(c).defaults = classBindings("class",c,cclass(c).defaults);
}

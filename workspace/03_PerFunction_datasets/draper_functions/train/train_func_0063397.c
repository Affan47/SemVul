findModAlias(t)
Text t; {
    List ms;
    for (ms = module(currentModule).modAliases; nonNull(ms); ms=tl(ms)) {
	if ( module(snd(hd(ms))).text == t ) {
	    return textOf(fst(hd(ms)));
	}
    }
    return NIL;
}

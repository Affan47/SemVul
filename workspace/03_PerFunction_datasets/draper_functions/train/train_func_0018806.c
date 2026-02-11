codeGen(n,arity,e)
Name n;
Int  arity;
Cell e; {
    definingName  = n;
    definingArity = arity;
#if DEBUG_CODE
    if (debugCode) {
	Printf("------------------\n");
	if (nonNull(n)) Printf("name=%s\n",textToStr(name(n).text));
	Printf("Arity   = %d\n",arity);
	Printf("codeGen = "); printExp(stdout,e); Putchar('\n');
    }
#endif
    asSTART();
    if (nonNull(n)) {
	Int i;
	for (i=1; i<=arity; i++)
	    offsPosn[i] = ++srsp;
	make(e,arity,noMatch,(arity>0 ? UPDRET : VALRET));
    }
    else {
	build(e,0);
	asRETURN();
    }
    asEND();
#if DEBUG_CODE
    if (debugCode) {
	if (nonNull(n))
	    Printf("name=%s\n",textToStr(name(n).text));
	dissassemble(startInstr,lastInstr);
	Printf("------------------\n");
    }
#endif
    return startInstr;
}

typeComp(l,m,e,qs)
Int  l;
Type m;
Cell e;
List qs; {
    static String boolQual = "boolean qualifier";
    static String genQual  = "generator";
#if IPARAM
    List svPreds;
#endif

    STACK_CHECK
    if (isNull(qs)) {
	spTypeExpr(l,fst(e));
    } else {
	Cell q   = hd(qs);
	List qs1 = tl(qs);
	switch (whatIs(q)) {
	    case BOOLQUAL : spCheck(l,snd(q),NIL,boolQual,typeBool,0);
			    typeComp(l,m,e,qs1);
			    break;

	    case QWHERE   : enterBindings();
			    enterSkolVars();
			    mapProc(typeBindings,snd(q));
			    typeComp(l,m,e,qs1);
			    leaveBindings();
			    leaveSkolVars(l,typeIs,typeOff,0);
			    break;

	    case FROMQUAL : {   Int beta = newTyvars(1);
				saveVarsAss();
				enterPendingBtyvs();
				spCheck(l,snd(snd(q)),NIL,genQual,m,beta);
				enterSkolVars();
				fst(snd(q))
				    = typeFreshPat(l,patBtyvs(fst(snd(q))));
				shouldBe(l,fst(snd(q)),NIL,genQual,aVar,beta);
				typeComp(l,m,e,qs1);
				restoreVarsAss();
			        leavePendingBtyvs();
				leaveSkolVars(l,typeIs,typeOff,0);
			    }
			    break;

	    case DOQUAL   : spCheck(l,snd(q),NIL,genQual,m,newTyvars(1));
			    typeComp(l,m,e,qs1);
			    break;
	}
    }
}

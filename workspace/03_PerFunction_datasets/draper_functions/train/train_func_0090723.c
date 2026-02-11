outputString(fp)
FILE *fp; {
    StackPtr origSp = sp;
    for (;;) {
	Cell temp = evalWithNoError(pop());
	if (nonNull(temp)) {
	    sp = origSp;
	    top()  = printException((top()=temp),nameNil);
	}
	else if (whnfHead==nameCons) {
	    if (nonNull(temp=evalWithNoError(pop()))) {
		sp = origSp;
		onto(temp);
		pushed(1) = printException(pushed(0),pushed(1));
		drop();
	    }
	    else {
		FPutChar(charOf(whnfHead),fp);
		fflush(fp);
	    }
	}
	else
	    return;
    }
}

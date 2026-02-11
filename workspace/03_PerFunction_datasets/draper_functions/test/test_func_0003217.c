checkNameAmbig(line,t,e)
Int line;
Text t;
Cell e; {
    Name n;

    if (isName(e)) {
	n = e;
    } else {
	n = findName(t);
    }
    checkNameAmbigName(line,n,TRUE);
}

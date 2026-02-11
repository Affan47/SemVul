conDefined(line,nm,check)
Int  line;
Cell nm;
Bool check; {
    Name n = findQualName(nm);
    if (isNull(n)) {
	ERRMSG(line) "Undefined data constructor \"%s\"", identToStr(nm)
	EEND;
    }
    checkIsCfun(line,n);
    if (check) {
      if (isQualIdent(nm)) {
	depQVar(line,nm,FALSE);
      } else {
	checkNameAmbigName(line,n,FALSE);
      }
    }
    return n;
}

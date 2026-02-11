attachFixity(line,op)
Int  line;
Cell op; {
    Syntax sy   = DEF_OPSYNTAX;
    Cell   trop = op;

    switch (whatIs(op)) {
	case VAROPCELL :
	case VARIDCELL : if ((sy=lookupSyntax(textOf(op)))==NO_SYNTAX) {
			     Name n = findName(textOf(op));
			     if (isNull(n)) {
				ERRMSG(line) "Undefined variable \"%s\"",
					     textToStr(textOf(op))
				EEND;
			     }
			     sy = syntaxOf(n);
			     trop = n;
			 }
			 break;

	case CONOPCELL :
	case CONIDCELL : sy = syntaxOf(trop = conDefined(line,op,FALSE));
			 break;

	case QUALIDENT : {   Name n = findQualName(op);
			     if (nonNull(n)) {
				 trop = n;
				 sy = syntaxOf(n);
			     } else {
				 ERRMSG(line)
				   "Undefined qualified variable \"%s\"",
				   identToStr(op)
				 EEND;
			     }
			 }
			 break;
    }
    if (sy==APPLIC) {
	sy = DEF_OPSYNTAX;
    }
    return pair(mkInt(sy),pair(trop,op));

}

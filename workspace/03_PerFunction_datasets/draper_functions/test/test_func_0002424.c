findModid(c)
Cell c; {
    switch (whatIs(c)) {
	case STRCELL   : { Script s = scriptThisFile(snd(c));
			   return (s==-1) ? NIL : moduleOfScript(s);
			 }
	case CONIDCELL : return findModule(textOf(c));
	default        : internal("findModid");
    }
    return NIL;
}

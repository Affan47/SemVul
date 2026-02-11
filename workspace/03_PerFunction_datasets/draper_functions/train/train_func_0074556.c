lowLevelLastOut(c)
Cell c; {
    if (isPair(c))
	if (isBoxTag(fst(c)))
	    switch (fst(c)) {
		case VARIDCELL :
		case VAROPCELL :
		case DICTVAR   :
		case CONIDCELL :
		case CONOPCELL :
		case STRCELL   : return pair(fst(c),
					     findText(text+intValOf(c)));
#if TREX
		case EXTCOPY   : return mkExt(findText(text+intValOf(c)));
#endif
		default        : return pair(fst(c),snd(c));
	    }
	else
	    return pair(lowLevelLastOut(fst(c)),lowLevelLastOut(snd(c)));
    else
	return c;
}

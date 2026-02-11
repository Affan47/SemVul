checkSubentities(imports,named,wanted,description,textParent)
List   imports;
List   named;
List   wanted;
String description;
Text   textParent; {
    for(; nonNull(named); named=tl(named)) {
	Pair x = hd(named);

	Text t = isPair(snd(x)) ? qtextOf(x) : textOf(x);
	Name n = lookupName(t,wanted);
	if (isNull(n)) {
	    ERRMSG(0) "Entity \"%s\" is not a %s \"%s\"",
		      textToStr(t),
		      description,
		      textToStr(textParent)
	    EEND;
	}
	imports = cons(n,imports);
    }
    return imports;
}

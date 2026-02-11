addNamesMatching(pat,ns)
String pat;
List   ns; {
    Name nm;
#if 1
    for (nm=NAMEMIN; nm<nameHw; ++nm)
	if (!inventedText(name(nm).text) && nonNull(name(nm).type)) {
	    String str = textToStr(name(nm).text);
	    if (str[0]!='_' && (!pat || stringMatch(pat,str)))
		ns = insertName(nm,ns);
	}
    return ns;
#else
    List mns = module(currentModule).names;
    for(; nonNull(mns); mns=tl(mns)) {
	Name nm = hd(mns);
	if (!inventedText(name(nm).text)) {
	    String str = textToStr(name(nm).text);
	    if (str[0]!='_' && (!pat || stringMatch(pat,str)))
		ns = insertName(nm,ns);
	}
    }
    return ns;
#endif
}

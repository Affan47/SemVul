get_class(FILE * fd, struct SigSet *S)
{
    char tag[1024];
    struct ClassSig *C;

    C = I_NewClassSig(S);
    while (gettag(fd, tag)) {
	if (eq(tag, "endclass:"))
	    break;
	if (eq(tag, "classnum:"))
	    get_classnum(fd, C);
	if (eq(tag, "classtype:"))
	    get_classtype(fd, C);
	if (eq(tag, "classtitle:"))
	    get_classtitle(fd, C);
	if (eq(tag, "subclass:"))
	    get_subclass(fd, S, C);
    }

    return 0;
}

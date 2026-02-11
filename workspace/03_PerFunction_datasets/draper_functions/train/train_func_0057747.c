FcValueListDestroy (FcValueListPtr l)
{
    FcValueListPtr next;
    for (; l; l = next)
    {
	switch ((int) l->value.type) {
	case FcTypeString:
	    FcFree (l->value.u.s);
	    break;
	case FcTypeMatrix:
	    FcMatrixFree ((FcMatrix *)l->value.u.m);
	    break;
	case FcTypeCharSet:
	    FcCharSetDestroy
		((FcCharSet *) (l->value.u.c));
	    break;
	case FcTypeLangSet:
	    FcLangSetDestroy
		((FcLangSet *) (l->value.u.l));
	    break;
	default:
	    break;
	}
	next = FcValueListNext(l);
	free(l);
    }
}

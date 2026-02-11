FcNameUnparseValue (FcStrBuf	*buf,
		    FcValue	*v0,
		    FcChar8	*escape)
{
    FcChar8	temp[1024];
    FcValue v = FcValueCanonicalize(v0);

    switch (v.type) {
    case FcTypeVoid:
	return FcTrue;
    case FcTypeInteger:
	sprintf ((char *) temp, "%d", v.u.i);
	return FcNameUnparseString (buf, temp, 0);
    case FcTypeDouble:
	sprintf ((char *) temp, "%g", v.u.d);
	return FcNameUnparseString (buf, temp, 0);
    case FcTypeString:
	return FcNameUnparseString (buf, v.u.s, escape);
    case FcTypeBool:
	return FcNameUnparseString (buf, v.u.b ? (FcChar8 *) "True" : (FcChar8 *) "False", 0);
    case FcTypeMatrix:
	sprintf ((char *) temp, "%g %g %g %g",
		 v.u.m->xx, v.u.m->xy, v.u.m->yx, v.u.m->yy);
	return FcNameUnparseString (buf, temp, 0);
    case FcTypeCharSet:
	return FcNameUnparseCharSet (buf, v.u.c);
    case FcTypeLangSet:
	return FcNameUnparseLangSet (buf, v.u.l);
    case FcTypeFTFace:
	return FcTrue;
    }
    return FcFalse;
}

FcListValueHash (FcValue    *value)
{
    FcValue v = FcValueCanonicalize(value);
    switch (v.type) {
    case FcTypeUnknown:
    case FcTypeVoid:
	return 0;
    case FcTypeInteger:
	return (FcChar32) v.u.i;
    case FcTypeDouble:
	return (FcChar32) (int) v.u.d;
    case FcTypeString:
	return FcStrHashIgnoreCase (v.u.s);
    case FcTypeBool:
	return (FcChar32) v.u.b;
    case FcTypeMatrix:
	return FcListMatrixHash (v.u.m);
    case FcTypeCharSet:
	return FcCharSetCount (v.u.c);
    case FcTypeFTFace:
	return (intptr_t) v.u.f;
    case FcTypeLangSet:
	return FcLangSetHash (v.u.l);
    case FcTypeRange:
	return FcRangeHash (v.u.r);
    }
    return 0;
}

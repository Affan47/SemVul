FcListValueListEqual (FcValueListPtr v1orig,
		      FcValueListPtr v2orig)
{
    FcValueListPtr	    v1, v2;

    for (v1 = v1orig; v1 != NULL; v1 = FcValueListNext(v1))
    {
	for (v2 = v2orig; v2 != NULL; v2 = FcValueListNext(v2))
	    if (FcValueEqual (FcValueCanonicalize(&(v1)->value),
			      FcValueCanonicalize(&(v2)->value)))
		break;
	if (v2 == NULL)
	    return FcFalse;
    }
    for (v2 = v2orig; v2 != NULL; v2 = FcValueListNext(v2))
    {
	for (v1 = v1orig; v1 != NULL; v1 = FcValueListNext(v1))
	    if (FcValueEqual (FcValueCanonicalize(&v1->value),
			      FcValueCanonicalize(&v2->value)))
		break;
	if (v1 == NULL)
	    return FcFalse;
    }
    return FcTrue;
}

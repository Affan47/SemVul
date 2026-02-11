FcValueListPrint (FcValueListPtr l)
{
    for (; l != NULL; l = FcValueListNext(l))
    {
	FcValuePrint (FcValueCanonicalize (&l->value));
	FcValueBindingPrint (l);
    }
}

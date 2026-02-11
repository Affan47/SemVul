FcCompareString (FcValue *v1, FcValue *v2)
{
    return (double) FcStrCmpIgnoreCase (FcValueString(v1), FcValueString(v2)) != 0;
}

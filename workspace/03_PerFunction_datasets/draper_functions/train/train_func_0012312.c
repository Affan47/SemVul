isAssetLiabType(GNCAccountType t)
{
    switch (t)
    {
    case ACCT_TYPE_RECEIVABLE:
    case ACCT_TYPE_PAYABLE:
        return FALSE;
    default:
        return (xaccAccountTypesCompatible(ACCT_TYPE_ASSET, t)
                || xaccAccountTypesCompatible(ACCT_TYPE_LIABILITY, t));
    }
}

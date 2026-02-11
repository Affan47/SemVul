FIFOPolicyGetLot (GNCPolicy *pcy, Split *split)
{
    if (!split) return NULL;
    return xaccAccountFindEarliestOpenLot (split->acc, split->amount,
                                           split->parent->common_currency);
}

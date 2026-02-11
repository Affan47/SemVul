cmp_charge_val( const void *a1, const void *a2 )
{
    const CHARGE_VAL *p1 = (const CHARGE_VAL *) a1;
    const CHARGE_VAL *p2 = (const CHARGE_VAL *) a2;
    int    diff;

    if ( diff = (int)p1->nValence - (int)p2->nValence )
        return diff;
    if ( diff = abs((int)p1->nCharge) - abs((int)p2->nCharge ))
        return diff;
    if ( diff = (int)p2->nCharge - (int)p1->nCharge )
        return diff;
    return (int)p1->nValenceOrderingNumber - (int)p2->nValenceOrderingNumber;
}

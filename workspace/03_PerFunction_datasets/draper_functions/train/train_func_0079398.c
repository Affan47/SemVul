BEncMessageContent PARAMS((b, v),
BUF_TYPE b _AND_
Message* v)
{
    AsnLen totalLen = 0;
    AsnLen itemLen;
    AsnLen listLen;
    void* component;

    itemLen = BEncPDUsContent( b, (v->data));

    totalLen += itemLen;

    itemLen = BEncAsnOctsContent( b, (&v->community));
    itemLen += BEncDefLen( b, itemLen);
    itemLen += BEncTag1(b, UNIV, PRIM, 4);

    totalLen += itemLen;

    itemLen = BEncMessageIntContent( b, (&v->version));
    BEncDefLenTo127( b, itemLen);
    itemLen++;
    itemLen += BEncTag1(b, UNIV, PRIM, 2);

    totalLen += itemLen;

    return (totalLen);

}

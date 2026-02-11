AsnOctsEquiv PARAMS((o1, o2),
AsnOcts* o1 _AND_
AsnOcts* o2)
{
    return( (o1->octetLen == o2->octetLen) && (memcmp(o1->octs, o2->octs, o1->octetLen) == 0));
}

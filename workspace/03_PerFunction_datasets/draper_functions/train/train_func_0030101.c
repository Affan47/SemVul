BDecApplicationSyntaxContent PARAMS((b, tagId0, elmtLen0, v, bytesDecoded, env),
BUF_TYPE b _AND_
AsnTag tagId0 _AND_
AsnLen elmtLen0 _AND_
ApplicationSyntax* v _AND_
AsnLen* bytesDecoded _AND_
ENV_TYPE env)
{
    int seqDone = FALSE;
    AsnLen totalElmtsLen1 = 0;
    AsnLen elmtLen1;
    AsnTag tagId1;
    int mandatoryElmtCount1 = 0;
    AsnLen totalElmtsLen2 = 0;
    AsnLen elmtLen2;
    AsnTag tagId2;


    switch(tagId0)
    {
       case(MAKE_TAG_ID( APPL, PRIM, 0)):
       case(MAKE_TAG_ID( APPL, CONS, 0)):
        (v->choiceId) = APPLICATIONSYNTAX_ADDRESS;
    (v->a.address) = (NetworkAddress*) Asn1Alloc(sizeof(NetworkAddress));
    CheckAsn1Alloc((v->a.address), env);
    BDecNetworkAddressContent( b, tagId0, elmtLen0, (v->a.address), &totalElmtsLen1, env);
    break;

       case(MAKE_TAG_ID( APPL, PRIM, 1)):
        (v->choiceId) = APPLICATIONSYNTAX_COUNTER;
    BDecCounterContent( b, tagId0, elmtLen0, (&v->a.counter), &totalElmtsLen1, env);
    break;

       case(MAKE_TAG_ID( APPL, PRIM, 2)):
        (v->choiceId) = APPLICATIONSYNTAX_GAUGE;
    BDecGaugeContent( b, tagId0, elmtLen0, (&v->a.gauge), &totalElmtsLen1, env);
    break;

       case(MAKE_TAG_ID( APPL, PRIM, 3)):
        (v->choiceId) = APPLICATIONSYNTAX_TICKS;
    BDecTimeTicksContent( b, tagId0, elmtLen0, (&v->a.ticks), &totalElmtsLen1, env);
    break;

       case(MAKE_TAG_ID( APPL, PRIM, 4)):
       case(MAKE_TAG_ID( APPL, CONS, 4)):
        (v->choiceId) = APPLICATIONSYNTAX_ARBITRARY;
    (v->a.arbitrary) = (Opaque*) Asn1Alloc(sizeof(Opaque));
    CheckAsn1Alloc((v->a.arbitrary), env);
    BDecOpaqueContent( b, tagId0, elmtLen0, (v->a.arbitrary), &totalElmtsLen1, env);
    break;

    default:
        Asn1Error("ERROR - unexpected tag in CHOICE\n");
        longjmp(env, -102);
        break;
    }
    (*bytesDecoded) += totalElmtsLen1;
}

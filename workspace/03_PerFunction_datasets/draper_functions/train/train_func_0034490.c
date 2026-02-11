pexp7 (void) {
    int ei0, ei1, ei2;

    ei0 = 0;
    switch (Ltok) {
    case L_FUNCTION:
        Lgtok ();
        ei0 =  pfunc ();
        break;
    case L_LP:
        ei0 = Cnew (C_PEXPR);
        Lgtok ();
        ei1 = pexpr ();
        GTOKIFEQ (L_RP);
        Csetfp (ei0, ei1);
        break;
    case L_LB:
        ei0 = ptcons ();
        break;
    case L_STRING:
    case L_NUMBER:
        ei0 = pcons ();
        break;
    case L_ID:
        ei0 = pvar ();
        if (Ltok == L_LP) {
            ei1 = ei0;
            ei0 = Cnew (C_FCALL);
            Csetfp (ei0, ei1);
            Lgtok ();
            ei2 = pargs ();
            Csetnext (ei1, ei2);
            GTOKIFEQ (L_RP);
        }
        break;
    default:
        err ("expected EXP7 type token, found: %s", Lnames[Ltok]);
    }
    return ei0;
}

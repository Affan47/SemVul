eforst (Tobj co, int ci) {
    volatile jmp_buf *opljbufp;
    volatile jmp_buf pljbuf;
    volatile Tobj c1o;
    volatile int ei1, ei2, ei3, si, eisnop1, eisnop2, eisnop3;

    Tobj v1o;

    c1o = (Tobj) co;
    ei1 = TCgetfp (c1o, ci);
    ei2 = TCgetnext (c1o, ei1);
    ei3 = TCgetnext (c1o, ei2);
    si = TCgetnext (c1o, ei3);
    eisnop1 = (TCgettype (c1o, ei1) == C_NOP);
    eisnop2 = (TCgettype (c1o, ei2) == C_NOP);
    eisnop3 = (TCgettype (c1o, ei3) == C_NOP);
    PUSHJMP (opljbufp, pljbufp1, pljbuf);
    if (!eisnop1)
        eeval ((Tobj) c1o, ei1);
    for (;;) {
        if (!eisnop2) {
            if (!(v1o = eeval ((Tobj) c1o, ei2)))
                err (ERRNORHS, ERR5, c1o, ei2);
            if (boolop (v1o) == FALSE)
                break;
        }
        if (setjmp (*pljbufp1) != 0) {
            if (pljtype == PLJ_CONTINUE)
                ;
            else if (pljtype == PLJ_BREAK)
                break;
        } else {
            eeval ((Tobj) c1o, si);
        }
        if (!eisnop3)
            eeval ((Tobj) c1o, ei3);
    }
    POPJMP (opljbufp, pljbufp1);
}

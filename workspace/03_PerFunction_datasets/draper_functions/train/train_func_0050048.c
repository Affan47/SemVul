op_name(beta_op op)
{
    static char opbuf[20];
    switch(op) {
#define OP(mnm) case mnm: return #mnm;
        ALL_OPS
#undef OP
    default:
        snprintf(opbuf, sizeof opbuf - 1, "ILLOP(%02x)", op);
        return opbuf;
    }
#undef CASE
}

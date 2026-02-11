depcase(void)
{
    int lev = 1;
    Aword i;


    if (singleStepOption) printf("\n    : ");
    while (TRUE) {
        i = memory[pc++];
        if (I_CLASS(i) == (Aword)C_STMOP)
            switch (I_OP(i)) {
            case I_DEPEND:
                lev++;
                break;
            case I_ENDDEP:
                lev--;
                if (lev == 0) {
                    pc--;
                    return;
                }
                break;
            }
    }
}

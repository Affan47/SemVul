goToLOOPEND(void) {
    int level = 1;
    int i;

    if (singleStepOption) traceSkip();
    while (TRUE) {

        i = memory[pc];
        if (I_CLASS(i) == (Aword)C_STMOP)
            switch (I_OP(i)) {
            case I_LOOPEND:
                level--;
                if (level == 0)
                    return;
                break;
            case I_LOOP:
                level++;
                break;
            }
        pc++;
    }
}

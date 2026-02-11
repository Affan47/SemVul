statement_SCCs_recurse(int entry)
{
    IntSet stm_dep_bv;
    int    num;

    N = N + 1;
    NPre[entry] = N;
    Lowlink[entry] = N;
    SCCs_stack[SCCs_index++] = entry;
    InStack[entry] = TRUE;

    stm_dep_bv = stm_table[entry].stm_dep_bv;
    num = 1;
    while(num < range_IntSet(stm_dep_bv)) {
        if (in_IntSet(stm_dep_bv, num)) {
            if (NPre[num] == 0) {
                statement_SCCs_recurse(num);
                Lowlink[entry] = min(Lowlink[entry], Lowlink[num]);
            } else if ((NPre[num] < NPre[entry]) && (InStack[num] == TRUE)) {
                Lowlink[entry] = min(Lowlink[entry], NPre[num]);
            }
        }
        num++;
    }

    if (NPre[entry] == Lowlink[entry]) {
        CountSCC = CountSCC + 1;

        for(;;) {
            if (SCCs_index <= 0) {
                mainlog("--- SCCs_stack invalid index ---");
                exit(-1);
            }
            num = SCCs_stack[--SCCs_index];
            InStack[num] = FALSE;
            stm_table[num].sccs_num = CountSCC;
            if (num == entry) {
                break;
            }
        }
    }

    return;
}

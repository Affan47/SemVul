sudokuCreate(l_int32  *array)
{
l_int32    i, val, locs_index;
L_SUDOKU  *sud;

    PROCNAME("sudokuCreate");

    if (!array)
        return (L_SUDOKU *)ERROR_PTR("array not defined", procName, NULL);

    locs_index = 0;
    if ((sud = (L_SUDOKU *)CALLOC(1, sizeof(L_SUDOKU))) == NULL)
        return (L_SUDOKU *)ERROR_PTR("sud not made", procName, NULL);
    if ((sud->locs = (l_int32 *)CALLOC(81, sizeof(l_int32))) == NULL)
        return (L_SUDOKU *)ERROR_PTR("su state array not made", procName, NULL);
    if ((sud->init = (l_int32 *)CALLOC(81, sizeof(l_int32))) == NULL)
        return (L_SUDOKU *)ERROR_PTR("su init array not made", procName, NULL);
    if ((sud->state = (l_int32 *)CALLOC(81, sizeof(l_int32))) == NULL)
        return (L_SUDOKU *)ERROR_PTR("su state array not made", procName, NULL);
    for (i = 0; i < 81; i++) {
        val = array[i];
        sud->init[i] = val;
        sud->state[i] = val;
        if (val == 0)
            sud->locs[locs_index++] = i;
    }
    sud->num = locs_index;
    sud->failure = FALSE;
    sud->finished = FALSE;
    return sud;
}

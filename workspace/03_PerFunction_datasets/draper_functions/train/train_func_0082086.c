FindFunction(int delta, int way) {
    RxNode     *regx;
    int         line;
    PELine      L;
    RxMatchRes  res;

    if (BFS(this, BFS_RoutineRegexp) == 0) {
        View->MView->Win->Choice(GPC_ERROR, "Error", 1,
                                 "O&K", "No routine regexp.");
        return -1;
    }
    regx = RxCompile(BFS(this, BFS_RoutineRegexp));
    if (regx == 0) {
        View->MView->Win->Choice(GPC_ERROR, "Error", 1,
                                 "O&K", "Failed to compile regexp '%s'",
                                 BFS(this, BFS_RoutineRegexp));
        return -1;
    }


    Msg(S_BUSY, "Matching %s", BFS(this, BFS_RoutineRegexp));
    line = VToR(CP.Row) + delta;
    while (line >= 0 && line < RCount) {
        L = RLine(line);
        if (RxExec(regx, L->Chars, L->Count, L->Chars, &res) == 1)
            break;
        line += way;
    }
    if (line < 0)
        line = 0;
    if (line >= RCount)
        line = RCount - 1;
    RxFree(regx);
    return line;
}

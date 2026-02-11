ChangeTabSize(ExState &State) {
    int No;

    if (State.GetIntParam(View, &No) == 0) {
        char Num[10];

        sprintf(Num, "%d", BFI(this, BFI_TabSize));
        if (View->MView->Win->GetStr("TabSize", sizeof(Num), Num, HIST_SETUP) == 0) return 0;
        No = atol(Num);
    }
    if (No < 1) return 0;
    if (No > 32) return 0;
    BFI(this, BFI_TabSize) = No;
    FullRedraw();
    return 1;
}

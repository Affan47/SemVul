ChangeFlags(ExState &State) {
    int rc;
    char Mode[32] = "";

    if (State.GetStrParam(View, Mode, sizeof(Mode)) == 0)
        if (View->MView->Win->GetStr("Mode", sizeof(Mode), Mode, HIST_SETUP) == 0) return 0;

    rc = ChangeFlags(Mode);
    FullRedraw();
    return rc;
}

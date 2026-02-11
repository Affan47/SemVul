Redo() {
    int rc;

    if (BFI(this, BFI_Undo) == 0) return 0;


    if (US.Num == 0 || US.UndoPtr == US.Num) {
        Msg(S_INFO, "Nothing to redo.");
        return 0;
    }

    US.Record = 0;
    rc =  Undo(0);
    US.Record = 1;
    return rc;
}

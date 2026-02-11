read(hsStream* S, plResManager* mgr) {
    if (S->readInt() != 0) {
        setX(new plScalarController());
        fXController->read(S, mgr);
    } else {
        setX(NULL);
    }
    if (S->readInt() != 0) {
        setY(new plScalarController());
        fYController->read(S, mgr);
    } else {
        setY(NULL);
    }
    if (S->readInt() != 0) {
        setZ(new plScalarController());
        fZController->read(S, mgr);
    } else {
        setZ(NULL);
    }
}

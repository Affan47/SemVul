read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fModelName = S->readSafeStr();
    fAccountName = S->readSafeStr();
    fAutoSpawn = S->readBool();

    if (S->readBool())
        setNotify(plNotifyMsg::Convert(mgr->ReadCreatable(S)));
}

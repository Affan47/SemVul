IRead(hsStream* S, plResManager* mgr) {
    fName = S->readSafeStr();
    fDataType = S->readInt();
    fNumber = S->readFloat();
    fKey = mgr->readKey(S);
}

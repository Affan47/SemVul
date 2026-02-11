Activate(int No) {
    SearchLen = 0;
    Msg(S_INFO, "");
    if (Files && No >= 0 && No < FCount) {
        if (isDir(No)) {
            FmChDir(Files[No]->Name());
            return 0;
        } else {
            return FmLoad(Files[No]->Name(), View);
        }
    }
    return 1;
}

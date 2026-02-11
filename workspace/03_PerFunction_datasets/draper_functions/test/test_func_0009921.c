ViewCvs(ExState &) {
    if (!CvsView)
        return 0;

    SwitchToModel(CvsView);
    return 1;
}

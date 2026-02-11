ClearSvnMessages(ExState &) {
    if (SvnView != 0) {
        if (SvnView->Running) {
            Msg(S_INFO, "Running...");
            return 0;
        } else {
            SvnView->FreeLines();
            SvnView->UpdateList();
            return 1;
        }
    }
    return 0;
}

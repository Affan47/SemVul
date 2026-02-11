windowStateChanged(FluxboxWindow &win) {
    STLUtil::forAllIf(m_atomhandler, mem_fun(&AtomHandler::update),
        CallMemFunWithRefArg<AtomHandler, FluxboxWindow&, void>(&AtomHandler::updateState, win));


    if (win.isIconic()) {
        win.screen().addIcon(&win);
        Workspace *space = win.screen().getWorkspace(win.workspaceNumber());
        if (space != 0)
            space->removeWindow(&win, true);
    }

    if (win.isStuck()) {


        BScreen &scr = win.screen();
        if (scr.currentWorkspaceID() != win.workspaceNumber())
            scr.reassociateWindow(&win, scr.currentWorkspaceID(), true);
    }
}

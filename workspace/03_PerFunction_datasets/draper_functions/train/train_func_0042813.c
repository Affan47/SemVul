enableCommands(YMenu *popup) {
    bool noItems = true;
    long workspace = -1;
    bool sameWorkspace = false;
    bool notHidden = false;
    bool notMinimized = false;


    popup->enableCommand(0);
    for (YListItem *i = getFirst(); i; i = i->getNext()) {
        if (isSelected(i)) {
            WindowListItem *item = (WindowListItem *)i;
            if (!item->getFrame()) {
                continue;
            }
            noItems = false;

            if (!item->getFrame()->isHidden())
                notHidden = true;
            if (!item->getFrame()->isMinimized())
                notMinimized = true;

            long ws = item->getFrame()->getWorkspace();
            if (workspace == -1) {
                workspace = ws;
                sameWorkspace = true;
            } else if (workspace != ws) {
                sameWorkspace = false;
            }
            if (item->getFrame()->isSticky())
                sameWorkspace = false;
        }
    }
    if (!notHidden)
        popup->disableCommand(actionHide);
    if (!notMinimized)
        popup->disableCommand(actionMinimize);

    moveMenu->enableCommand(0);
    if (sameWorkspace && workspace != -1) {
        for (int i = 0; i < moveMenu->itemCount(); i++) {
            YMenuItem *item = moveMenu->getItem(i);
            for (int w = 0; w < workspaceCount; w++)
                if (item && item->getAction() == workspaceActionMoveTo[w])
                    item->setEnabled(w != workspace);
        }
    }
    if (noItems) {
        moveMenu->disableCommand(0);
        popup->disableCommand(0);
    }
}

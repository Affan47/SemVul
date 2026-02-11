maxLeft(int head) const {


    if (hasXinerama())
        return doFullMax() ? getHeadX(head) :
            getHeadX(head) + availableWorkspaceArea(head)->left();
    else
        return doFullMax() ? 0 : availableWorkspaceArea(head)->left();
}

LocalMenu(GxView *View) {
    EEventMap *Map = View->GetEventMap();
    const char *MName = 0;

    if (Map)
        MName = Map->GetMenu(EM_LocalMenu);
    if (MName == 0)
        MName = "Local";

    View->Parent->PopupMenu(MName);

    return 1;
}

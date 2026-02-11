CreateWatches()
{
    WatchesDlg *dialog = new WatchesDlg;
    CodeBlocksDockEvent evt(cbEVT_ADD_DOCK_WINDOW);
    evt.name = _T("WatchesPane");
    evt.title = _("Watches (new)");
    evt.pWindow = dialog;
    evt.dockSide = CodeBlocksDockEvent::dsFloating;
    evt.desiredSize.Set(150, 250);
    evt.floatingSize.Set(150, 250);
    evt.minimumSize.Set(150, 150);
    Manager::Get()->ProcessEvent(evt);
    return dialog;
}

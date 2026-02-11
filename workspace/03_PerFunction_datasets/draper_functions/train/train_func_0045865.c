SendCloseEvent()
{
    wxWindow* topLevel = GetParent();
    while (topLevel && !topLevel->IsTopLevel())
        topLevel = topLevel->GetParent();

    if (topLevel)
    {
        wxCloseEvent closeEvent(wxEVT_CLOSE_WINDOW, topLevel->GetId());
        closeEvent.SetEventObject(topLevel);
        closeEvent.SetCanVeto(false);

        topLevel->GetEventHandler()->ProcessEvent(closeEvent);
        return;
    }
}

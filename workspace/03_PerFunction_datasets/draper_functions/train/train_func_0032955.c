addChart(QAction*action)
{
    GcWinID id = GcWindowTypes::None;
    for (int i=0; GcWindows[i].relevance; i++) {
        if (GcWindows[i].name == action->text()) {
            id = GcWindows[i].id;
            break;
        }
    }
    if (id != GcWindowTypes::None)
        currentWindow->appendChart(id);
}

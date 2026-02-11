SetTitle(const char *ATitle) {
    free(Title);
    Title = strdup(ATitle);
    if (View && View->MView)
        View->MView->RepaintStatus();
}

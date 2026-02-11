intervalCount() const
{
    int highlighted;
    highlighted = 0;
    if (mainWindow->allIntervalItems() == NULL) return 0;

    for (int i=0; i<mainWindow->allIntervalItems()->childCount(); i++) {
        IntervalItem *current = dynamic_cast<IntervalItem *>(mainWindow->allIntervalItems()->child(i));
        if (current != NULL) {
            if (current->isSelected() == true) {
                ++highlighted;
            }
        }
    }
    return highlighted;
}

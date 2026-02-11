isSelected(const RideFilePoint *p, double sample) {
    if (mainWindow->allIntervalItems() != NULL) {
        for (int i=0; i<mainWindow->allIntervalItems()->childCount(); i++) {
            IntervalItem *current = dynamic_cast<IntervalItem*>(mainWindow->allIntervalItems()->child(i));
            if (current != NULL) {
                if (current->isSelected() && p->secs+sample>current->start && p->secs<current->stop) {
                    return true;
                }
            }
        }
    }
    return false;
}

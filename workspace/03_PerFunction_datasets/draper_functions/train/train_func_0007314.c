GProgressShow(void) {

    if ( current==NULL || current->visible || current->dying )
return;

    GProgressDisplay();
    GDrawSync(NULL);
    GDrawProcessPendingEvents(NULL);
    GDrawSync(NULL);
    GDrawProcessPendingEvents(NULL);
}

checkDependency(void *context, const char *itemName, const char *targetName) {

    Package *me=(Package *)context;
    if(me->findItem(targetName)<0) {
        me->isMissingItems=TRUE;
        fprintf(stderr, "Item %s depends on missing item %s\n", itemName, targetName);
    }
}

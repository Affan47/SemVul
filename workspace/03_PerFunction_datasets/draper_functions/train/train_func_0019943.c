markRoot(Object *object) {
    if(object != NULL)
        MARK(object, HARD_MARK);
}

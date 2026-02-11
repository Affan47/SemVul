isMarkedJNIWeakGlobalRef(Object *object) {
    int marked = IS_MARKED(object);

    if(marked)
        addConservativeRoot(object);
    else {
        TRACE_GC("Converting JNI weak global reference @%p to place holder",
                 object);
        convertToPlaceholder(object);
    }

    return marked;
}

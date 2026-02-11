getDeclaringClass(Class *class) {
    ClassBlock *cb = CLASS_CB(class);

    return cb->declaring_class ? resolveClass(class, cb->declaring_class,
                                              TRUE, FALSE)
                               : NULL;
}

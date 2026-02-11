JVM_AssertionStatusDirectives(JNIEnv *env, jclass unused) {
    Class *asd_class = findSystemClass("java/lang/AssertionStatusDirectives");
    Class *string_class = findArrayClass(SYMBOL(array_java_lang_String));
    FieldBlock *classes_fb, *packages_fb;
    Object *asd, *names;

    TRACE("JVM_AssertionStatusDirectives(env=%p, unused=%p)", env, unused);

    if(asd_class == NULL || string_class == NULL)
        return NULL;

    classes_fb = findField(asd_class, SYMBOL(classes),
                                      SYMBOL(array_java_lang_String));
    packages_fb = findField(asd_class, newUtf8("packages"),
                                       SYMBOL(array_java_lang_String));

    asd = allocObject(asd_class);
    names = allocArray(string_class, 0, sizeof(Object*));

    if(asd == NULL)
        return NULL;

    INST_DATA(asd, Object*, classes_fb->u.offset) = names;
    INST_DATA(asd, Object*, packages_fb->u.offset) = names;

    return asd;
}

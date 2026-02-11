setProperty(Object *properties, char *key, char *value) {
    Object *k = Cstr2String(key);
    Object *v = Cstr2String(value ? value : "?");

    MethodBlock *mb = lookupMethod(properties->class, SYMBOL(put),
                  SYMBOL(_java_lang_Object_java_lang_Object__java_lang_Object));
    executeMethod(properties, mb, k, v);
}

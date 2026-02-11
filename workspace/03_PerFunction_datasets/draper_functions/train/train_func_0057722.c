Jam_NewObjectArray(JNIEnv *env, jsize length, jclass elementClass_ref,
                          jobject initialElement_ref) {

    Object *initial_element = REF_TO_OBJ(initialElement_ref);
    Class *element_class = REF_TO_OBJ(elementClass_ref);
    Object *array;

    if(length < 0) {
        signalException(java_lang_NegativeArraySizeException, NULL);
        return NULL;
    }

    array = allocObjectArray(element_class, length);

    if(array != NULL && initial_element != NULL) {
        Object **data = ARRAY_DATA(array, Object*);

        while(length--)
           *data++ = initial_element;
    }

    return addJNILref(array);
}

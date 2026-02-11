getAnnotationsAsArray(AttributeData *annotations) {
    Object *array;

    if(annotations == NULL)
        return NULL;

    if((array = allocTypeArray(T_BYTE, annotations->len)) == NULL)
        return NULL;

    memcpy(ARRAY_DATA(array, void*), annotations->data, annotations->len);

    return array;
}

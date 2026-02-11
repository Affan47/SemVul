cf_object_set_nrof(object *ob, int nrof) {
    int type;

    if (nrof < 0)
        return -1;

    cfapiObject_set_property(&type, ob, CFAPI_OBJECT_PROP_NROF, nrof);
    return 0;
}

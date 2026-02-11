Object_GetPickable(Crossfire_Object *whoptr, void *closure) {
    EXISTCHECK(whoptr);
    return Py_BuildValue("i", !cf_object_get_flag(whoptr->obj, FLAG_NO_PICK));
}

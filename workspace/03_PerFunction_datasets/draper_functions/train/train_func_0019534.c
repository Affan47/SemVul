cm_clear(classmethod *cm)
{
    Py_CLEAR(cm->cm_callable);
    return 0;
}

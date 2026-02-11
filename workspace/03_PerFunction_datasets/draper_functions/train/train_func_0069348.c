PySys_SetArgvEx(int argc, wchar_t **argv, int updatepath)
{
    PyObject *av = makeargvobject(argc, argv);
    if (av == NULL)
        Py_FatalError("no mem for sys.argv");
    if (PySys_SetObject("argv", av) != 0)
        Py_FatalError("can't assign sys.argv");
    Py_DECREF(av);
    if (updatepath)
        sys_update_path(argc, argv);
}

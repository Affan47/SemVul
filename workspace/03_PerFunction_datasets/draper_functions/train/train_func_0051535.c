Crossfire_Map_Long(PyObject *obj) {
    MAPEXISTCHECK((Crossfire_Map *)obj);
    return Py_BuildValue("l", ((Crossfire_Map *)obj)->map);
}

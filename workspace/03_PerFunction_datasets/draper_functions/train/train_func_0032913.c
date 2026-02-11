_dict_to_assoc (dico_assoc_list_t assoc, PyObject *py_dict)
{
    PyObject *py_key, *py_value;
    Py_ssize_t py_pos = 0;

    dico_assoc_clear (assoc);

    while (PyDict_Next (py_dict, &py_pos, &py_key, &py_value)) {
	char *key, *val;
	key = strdup (PyString_AsString (py_key));
	val = strdup (PyString_AsString (py_value));
	dico_assoc_append (assoc, key, val);
    }
}

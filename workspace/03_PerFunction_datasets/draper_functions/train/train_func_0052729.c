tree_entries(char *path, Py_ssize_t path_len, PyObject *tree,
		Py_ssize_t *n)
{
	PyObject *iteritems, *items, **result = NULL;
	PyObject *old_entry, *name, *sha;
	Py_ssize_t i = 0, name_len, new_path_len;
	char *new_path;

	if (tree == Py_None) {
		*n = 0;
		result = PyMem_New(PyObject*, 0);
		if (!result) {
			PyErr_SetNone(PyExc_MemoryError);
			return NULL;
		}
		return result;
	}

	iteritems = PyObject_GetAttrString(tree, "iteritems");
	if (!iteritems)
		return NULL;
	items = PyObject_CallFunctionObjArgs(iteritems, Py_True, NULL);
	Py_DECREF(iteritems);
	if (!items) {
		return NULL;
	}

	if (!PyList_Check(items)) {
		PyErr_SetString(PyExc_TypeError,
			"Tree.iteritems() did not return a list");
		return NULL;
	}

	*n = PyList_Size(items);
	result = PyMem_New(PyObject*, *n);
	if (!result) {
		PyErr_SetNone(PyExc_MemoryError);
		goto error;
	}
	for (i = 0; i < *n; i++) {
		old_entry = PyList_GetItem(items, i);
		if (!old_entry)
			goto error;
		sha = PyTuple_GetItem(old_entry, 2);
		if (!sha)
			goto error;
		name = PyTuple_GET_ITEM(old_entry, 0);
		name_len = PyString_Size(name);
		if (PyErr_Occurred())
			goto error;

		new_path_len = name_len;
		if (path_len)
			new_path_len += path_len + 1;
		new_path = PyMem_Malloc(new_path_len);
		if (!new_path) {
			PyErr_SetNone(PyExc_MemoryError);
			goto error;
		}
		if (path_len) {
			memcpy(new_path, path, path_len);
			new_path[path_len] = '/';
			memcpy(new_path + path_len + 1, PyString_AS_STRING(name), name_len);
		} else {
			memcpy(new_path, PyString_AS_STRING(name), name_len);
		}

		result[i] = PyObject_CallFunction(tree_entry_cls, "s#OO", new_path,
			new_path_len, PyTuple_GET_ITEM(old_entry, 1), sha);
		PyMem_Free(new_path);
		if (!result[i]) {
			goto error;
		}
	}
	Py_DECREF(items);
	return result;

error:
	free_objects(result, i);
	Py_DECREF(items);
	return NULL;
}

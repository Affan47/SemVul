t_Modifier_isPrivate(PyTypeObject *type, PyObject *arg)
            {
                if (!PyInt_Check(arg))
                {
                    PyErr_SetObject(PyExc_TypeError, arg);
                    return NULL;
                }

                int mod = PyInt_AsLong(arg);
                int isPrivate;

                OBJ_CALL(isPrivate = Modifier::isPrivate(mod));
                Py_RETURN_BOOL(isPrivate);
            }

t_String_init(t_String *self,
                                 PyObject *args, PyObject *kwds)
        {
            char *bytes;

            switch (PyTuple_Size(args)) {
              case 0:
                INT_CALL(self->object = String());
                break;
              case 1:
                if (!PyArg_ParseTuple(args, "s", &bytes))
                    return -1;
                INT_CALL(self->object = String(env->fromUTF(bytes)));
                break;
              default:
                PyErr_SetString(PyExc_ValueError, "invalid args");
                return -1;
            }

            return 0;
        }

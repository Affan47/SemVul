PyListOrTuple_GET_SIZE(PyObject* pyobj)
        {
            if(PyList_Check(pyobj))
            {
                return static_cast<int>(PyList_GET_SIZE(pyobj));
            }
            else if(PyTuple_Check(pyobj))
            {
                return static_cast<int>(PyTuple_GET_SIZE(pyobj));
            }
            return -1;
        }

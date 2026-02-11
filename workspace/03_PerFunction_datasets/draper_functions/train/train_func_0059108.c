GetStringFromPyObject(PyObject* object, std::string* val)
    {
        if(!val || !object) return false;

        if( PyString_Check( object ) )
        {
            *val = std::string(PyString_AS_STRING(object));
            return true;
        }

        PyObject* strObject = PyObject_Str(object);
        if(strObject)
        {
            *val = std::string(PyString_AS_STRING(strObject));
            Py_DECREF(strObject);
            return true;
        }

        PyErr_Clear();
        return false;
    }

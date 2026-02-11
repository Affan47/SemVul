ConvertPyObjectToGpuLanguage(PyObject *object, void *valuePtr)
    {
        GpuLanguage* gpuLanguagePtr = static_cast<GpuLanguage*>(valuePtr);

        if(!PyString_Check(object))
        {
            PyErr_SetString(PyExc_ValueError, "Object is not a string.");
            return 0;
        }

        *gpuLanguagePtr = GpuLanguageFromString(PyString_AsString( object ));

        return 1;
    }

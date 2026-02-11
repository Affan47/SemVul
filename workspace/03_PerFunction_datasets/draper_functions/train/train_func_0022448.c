pytype_check(PyTypeObject* type_, PyObject* source)
{
    if (!PyObject_IsInstance(source, python::upcast<PyObject>(type_)))
    {
        ::PyErr_Format(
            PyExc_TypeError
            , "Expecting an object of type %s; got an object of type %s instead"
            , type_->tp_name
            , source->ob_type->tp_name
            );
        throw_error_already_set();
    }
    return source;
}

}}

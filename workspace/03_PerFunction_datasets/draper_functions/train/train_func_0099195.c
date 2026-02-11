find(object_cref sub, object_cref start, object_cref end) const
{
    long result = _BOOST_PYTHON_ASLONG(this->attr("find")(sub,start,end).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

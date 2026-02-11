get_lvalue_from_python(
    PyObject* source
    , registration const& converters)
{

    void* x = objects::find_instance_impl(source, converters.target_type);
    if (x)
        return x;

    lvalue_from_python_chain const* chain = converters.lvalue_chain;
    for (;chain != 0; chain = chain->next)
    {
        void* r = chain->convert(source);
        if (r != 0)
            return r;
    }
    return 0;
}

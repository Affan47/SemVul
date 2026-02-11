to_python(PyTypeObject* type_, long x)
{
    object type((type_handle(borrowed(type_))));

    dict d = extract<dict>(type.attr("values"))();
    object v = d.get(x, object());
    return incref(
        (v == object() ? type(x) : v).ptr());
}

}}

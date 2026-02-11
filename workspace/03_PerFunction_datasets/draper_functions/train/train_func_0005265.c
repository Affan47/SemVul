setLocal(CallFrame& c, const ObjectURI& name, const as_value& val)
{
    as_object& locals = c.locals();


    Property* prop = locals.getOwnProperty(name);
    if (prop) {
        prop->setValue(locals, val);
        return;
    }

    locals.set_member(name, val);
}

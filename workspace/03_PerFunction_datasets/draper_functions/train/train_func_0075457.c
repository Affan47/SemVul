fromPropertyDescriptor(ExecState *exec)
{
    JSObject *ret = new JSObject(exec->lexicalInterpreter()->builtinObjectPrototype());

    if (isDataDescriptor()) {
        ret->put(exec, exec->propertyNames().writable, jsBoolean(writable()));
        ret->put(exec, exec->propertyNames().value, value() ? value() : jsUndefined());
    } else {
        ret->put(exec, exec->propertyNames().get, getter() ? getter() : jsUndefined());
        ret->put(exec, exec->propertyNames().set, setter() ? setter() : jsUndefined());
    }

    ret->put(exec, exec->propertyNames().enumerable, jsBoolean(enumerable()));
    ret->put(exec, exec->propertyNames().configurable, jsBoolean(configurable()));

    return ret;
}

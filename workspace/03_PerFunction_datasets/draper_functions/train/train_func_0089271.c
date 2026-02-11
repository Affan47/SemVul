callAsFunction(ExecState* exec, JSObject*, const List& args)
{
    switch (id) {
    case IsArray: {
        JSObject* jso = args[0]->getObject();
        if (!jso)
            return jsBoolean(false);
        return jsBoolean(jso->inherits(&ArrayInstance::info));
    }
    default:
        return jsUndefined();
    }
}

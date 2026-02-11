put(ExecState* exec, unsigned i, JSValue* value, int attributes)
{
    ArrayEntity *ent = getArrayEntity(i);
    if (ent) {
        if (ent->attributes & ReadOnly)
            return;
        attributes |= ent->attributes;

        JSValue* gs = ent->value;
        if (gs && !gs->isUndefined()) {
            if (ent->attributes & GetterSetter) {
                JSObject *setterFunc = static_cast<GetterSetterImp *>(gs)->getSetter();

                if (!setterFunc) {
                    if (false)
                        throwError(exec, TypeError, "setting a property that has only a getter");
                    return;
                }

                List args;
                args.append(value);

                setterFunc->call(exec, this, args);
                return;
            }
        }
    }

    KJS::ArrayInstance::putDirect(i, value, attributes);
}

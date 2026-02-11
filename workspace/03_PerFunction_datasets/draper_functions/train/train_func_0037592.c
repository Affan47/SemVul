put(ExecState* exec, const Identifier& propertyName, JSValue* value, int attributes)
{
    bool isArrayIndex;
    unsigned i = propertyName.toArrayIndex(&isArrayIndex);
    if (isArrayIndex) {
        put(exec, i, value, attributes);
        return;
    }

    if (propertyName == exec->propertyNames().length) {
        if (m_lengthAttributes & ReadOnly)
            return;
        unsigned newLength = value->toUInt32(exec);
        if (value->toNumber(exec) != static_cast<double>(newLength)) {
            throwError(exec, RangeError, "Invalid array length.");
            return;
        }
        m_lengthAttributes = attributes;
        setLength(newLength);
        return;
    }

    JSObject::put(exec, propertyName, value, attributes);
}

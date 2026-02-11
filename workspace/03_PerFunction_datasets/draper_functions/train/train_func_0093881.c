getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& desc)
{
    if (propertyName == exec->propertyNames().length) {
        desc.setPropertyDescriptorValues(exec, jsNumber(internalValue()->value().size()), ReadOnly|DontDelete|DontEnum);
        return true;
    }

    return KJS::JSObject::getOwnPropertyDescriptor(exec, propertyName, desc);
}

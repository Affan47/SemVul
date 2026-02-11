addProperty(const QMetaProperty& prototype)
{
    QMetaPropertyBuilder property = addProperty(prototype.name(), prototype.typeName());
    property.setReadable(prototype.isReadable());
    property.setWritable(prototype.isWritable());
    property.setResettable(prototype.isResettable());
    property.setDesignable(prototype.isDesignable());
    property.setScriptable(prototype.isScriptable());
    property.setStored(prototype.isStored());
    property.setEditable(prototype.isEditable());
    property.setUser(prototype.isUser());
    property.setStdCppSet(prototype.hasStdCppSet());
    property.setEnumOrFlag(prototype.isEnumType());
    property.setConstant(prototype.isConstant());
    property.setFinal(prototype.isFinal());
    if (prototype.hasNotifySignal()) {

        QMetaMethod method = prototype.notifySignal();
        int index = indexOfMethod(method.signature());
        if (index == -1)
            index = addMethod(method).index();
        d->properties[property._index].notifySignal = index;
        d->properties[property._index].setFlag(Notify, true);
    }
    return property;
}

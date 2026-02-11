pluginRootGet(ExecState* exec, ScriptableExtension* ext, const KJS::Identifier& i, PropertySlot& slot)
{
    ScriptableExtension::Object rootObj = grabRoot(ext);
    if (!rootObj.owner)
        return false;

    QVariant v = rootObj.owner->get(0 ,
                                       rootObj.objId, i.qstring());

    bool ok = false;
    if (!isException(v)) {
        getImmediateValueSlot(0, ScriptableOperations::importValue(exec, v, true), slot);
        ok = true;
    }

    rootObj.owner->release(rootObj.objId);
    return ok;
}

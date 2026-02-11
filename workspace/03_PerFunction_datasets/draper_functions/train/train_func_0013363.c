deleteProperty(ExecState* exec, const Identifier& i)
{
    bool ok;
    ScriptableExtension::Object actualObj = resolveAnyReferences(exec, &ok);

    if (!ok)
        return false;

    return actualObj.owner->removeProperty(principal(exec),
                                           actualObj.objId, i.qstring());
}

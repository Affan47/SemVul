importObject(ExecState* exec, const QVariant& v, bool alreadyRefd)
{
    ScriptableExtension::Object obj = v.value<ScriptableExtension::Object>();
    if (JSObject* our = tryGetNativeObject(obj)) {
        return our;
    } else {


        if (WrapScriptableObject* old = importedObjects()->value(obj)) {
            if (alreadyRefd)
                old->reportRef();
            return old;
        } else {
            WrapScriptableObject* wrap =
                new WrapScriptableObject(exec, WrapScriptableObject::Object,
                                         obj.owner, obj.objId);
            importedObjects()->insert(obj, wrap);
            if (alreadyRefd)
                wrap->reportRef();
            return wrap;
        }
    }
}

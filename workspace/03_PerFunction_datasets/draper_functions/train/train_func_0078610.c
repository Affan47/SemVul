acquireValue(const QVariant& v)
{
    if (v.canConvert<Object>()) {
        Object o = v.value<Object>();
        o.owner->acquire(o.objId);
    } else if (v.canConvert<FunctionRef>()) {
        FunctionRef fr = v.value<FunctionRef>();
        fr.base.owner->acquire(fr.base.objId);
    }
    return v;
}

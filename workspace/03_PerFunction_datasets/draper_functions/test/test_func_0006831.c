getValueProperty(ExecState* exec, int token) const
{
    switch (token) {
    case CodeAttrNum: {
        MediaError* imp = static_cast<MediaError*>(impl());

        return jsNumber(imp->code());
    }
    case ConstructorAttrNum:
        return getConstructor(exec);
    }
    return 0;
}

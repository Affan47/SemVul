constructArrayHelper(ExecState* exec, int len)
{
    JSObject* builtinArray = exec->lexicalInterpreter()->builtinArray();
    JSObject* newArray = builtinArray->construct(exec, List());
    newArray->put(exec, exec->propertyNames().length, jsNumber(len),
                  DontDelete|ReadOnly|DontEnum);
    return newArray;
}

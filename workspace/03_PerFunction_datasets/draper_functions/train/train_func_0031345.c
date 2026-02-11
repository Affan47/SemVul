compareValue(ExecState* exec, JSValue* a, JSValue* b)
{
    return (a == b || (a && b && sameValue(exec, a, b)));
}

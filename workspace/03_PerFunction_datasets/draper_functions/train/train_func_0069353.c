ctfeInterpret()
{
    if (type == Type::terror)
        return this;


    CompiledCtfeFunction ctfeCodeGlobal(NULL);
    ctfeCodeGlobal.callingloc = loc;
    ctfeCodeGlobal.onExpression(this);

    Expression *e = interpret(NULL);
    if (e != EXP_CANT_INTERPRET)
        e = scrubReturnValue(loc, e);
    if (e == EXP_CANT_INTERPRET)
        e = new ErrorExp();
    return e;
}

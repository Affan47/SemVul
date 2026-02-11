check_aop_type(Type left, Type right, u1 opcode)
{
    if (iseq(left, right))
    {
        if (isint(left))
            emit(iadd);
        else if (isfloat(left))
            emit(fadd);
        else
            error("Unsupported operand");
    }
    else
        error("Type error");
}

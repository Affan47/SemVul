equals(RootObject *o)
{
    if (this == o)
        return true;
    if (((Expression *)o)->op == TOKfloat64)
    {
        RealExp *ne = (RealExp *)o;
        if (type->toHeadMutable()->equals(ne->type->toHeadMutable()) &&
            RealEquals(value, ne->value))
        {
            return true;
        }
    }
    return false;
}

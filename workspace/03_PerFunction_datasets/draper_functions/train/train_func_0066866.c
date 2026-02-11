toExpression(Type *t)
{
    if (t)
    {
        Type *tb = t->toBasetype();
        if (tb->ty == Tsarray && exp->implicitConvTo(tb->nextOf()))
        {
            TypeSArray *tsa = (TypeSArray *)tb;
            size_t d = tsa->dim->toInteger();
            Expressions *elements = new Expressions();
            elements->setDim(d);
            for (size_t i = 0; i < d; i++)
                (*elements)[i] = exp;
            ArrayLiteralExp *ae = new ArrayLiteralExp(exp->loc, elements);
            ae->type = t;
            exp = ae;
        }
    }
    return exp;
}

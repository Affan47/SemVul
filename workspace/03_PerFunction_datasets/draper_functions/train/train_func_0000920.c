optimize(int result, bool keepLvalue)
{   Expression *e;


    e = this;
    e1 = e1->optimize(WANTvalue | (result & WANTexpand));
    if (!lwr)
    {   if (e1->op == TOKstring)
        {
            Type *t = e1->type->toBasetype();
            if (t->nextOf())
                e = e1->castTo(NULL, t->nextOf()->arrayOf());
        }
        return e;
    }
    e1 = fromConstInitializer(result, e1);

    setLengthVarIfKnown(lengthVar, e1);
    lwr = lwr->optimize(WANTvalue);
    upr = upr->optimize(WANTvalue);
    e = Slice(type, e1, lwr, upr);
    if (e == EXP_CANT_INTERPRET)
        e = this;

    return e;
}

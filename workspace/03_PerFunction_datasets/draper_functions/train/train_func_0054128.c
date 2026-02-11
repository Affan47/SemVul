Slice(Type *type, Expression *e1, Expression *lwr, Expression *upr)
{   Expression *e = EXP_CANT_INTERPRET;
    Loc loc = e1->loc;

#if LOG
    printf("Slice()\n");
    if (lwr)
    {   printf("\te1 = %s\n", e1->toChars());
        printf("\tlwr = %s\n", lwr->toChars());
        printf("\tupr = %s\n", upr->toChars());
    }
#endif
    if (e1->op == TOKstring && lwr->op == TOKint64 && upr->op == TOKint64)
    {   StringExp *es1 = (StringExp *)e1;
        uinteger_t ilwr = lwr->toInteger();
        uinteger_t iupr = upr->toInteger();

        if (iupr > es1->len || ilwr > iupr)
        {
            e1->error("string slice [%llu .. %llu] is out of bounds", ilwr, iupr);
            e = new ErrorExp();
        }
        else
        {
            void *s;
            size_t len = iupr - ilwr;
            int sz = es1->sz;
            StringExp *es;

            s = mem.malloc((len + 1) * sz);
            memcpy((utf8_t *)s, (utf8_t *)es1->string + ilwr * sz, len * sz);
            memset((utf8_t *)s + len * sz, 0, sz);

            es = new StringExp(loc, s, len, es1->postfix);
            es->sz = sz;
            es->committed = es1->committed;
            es->type = type;
            e = es;
        }
    }
    else if (e1->op == TOKarrayliteral &&
            lwr->op == TOKint64 && upr->op == TOKint64 &&
            !e1->hasSideEffect())
    {   ArrayLiteralExp *es1 = (ArrayLiteralExp *)e1;
        uinteger_t ilwr = lwr->toInteger();
        uinteger_t iupr = upr->toInteger();

        if (iupr > es1->elements->dim || ilwr > iupr)
        {
            e1->error("array slice [%llu .. %llu] is out of bounds", ilwr, iupr);
            e = new ErrorExp();
        }
        else
        {
            Expressions *elements = new Expressions();
            elements->setDim(iupr - ilwr);
            memcpy(elements->tdata(),
                   es1->elements->tdata() + ilwr,
                   (iupr - ilwr) * sizeof((*es1->elements)[0]));
            e = new ArrayLiteralExp(e1->loc, elements);
            e->type = type;
        }
    }
    return e;
}

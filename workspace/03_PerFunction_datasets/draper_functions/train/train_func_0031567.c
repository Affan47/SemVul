arrayObjectHash(Objects *oa1)
{
    hash_t hash = 0;
    for (size_t j = 0; j < oa1->dim; j++)
    {

        RootObject *o1 = (*oa1)[j];
        if (Type *t1 = isType(o1))
            hash += (size_t)t1->deco;
        else
        {
            Dsymbol *s1 = isDsymbol(o1);
            Expression *e1 = s1 ? getValue(s1) : getValue(isExpression(o1));
            if (e1)
            {
                if (e1->op == TOKint64)
                {
                    IntegerExp *ne = (IntegerExp *)e1;
                    hash += (size_t)ne->value;
                }
            }
            else if (s1)
            {
                FuncAliasDeclaration *fa1 = s1->isFuncAliasDeclaration();
                if (fa1)
                    s1 = fa1->toAliasFunc();
                hash += (size_t)(void *)s1->getIdent() + (size_t)(void *)s1->parent;
            }
            else if (Tuple *u1 = isTuple(o1))
                hash += arrayObjectHash(&u1->objects);
        }
    }
    return hash;
}

isFunctionParameter(Dsymbol *s, utf8_t *p, size_t len)
{
    TypeFunction *tf = isTypeFunction(s);
    if (tf && tf->parameters)
    {
        for (size_t k = 0; k < tf->parameters->dim; k++)
        {
            Parameter *arg = (*tf->parameters)[k];
            if (arg->ident && cmp(arg->ident->toChars(), p, len) == 0)
            {
                return arg;
            }
        }
    }
    return NULL;
}

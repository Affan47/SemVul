apply(Dsymbol_apply_ft_t fp, void *param)
{
    Dsymbols *d = include(scope, NULL);

    if (d)
    {
        for (size_t i = 0; i < d->dim; i++)
        {   Dsymbol *s = (*d)[i];
            if (s)
            {
                if (s->apply(fp, param))
                    return 1;
            }
        }
    }
    return 0;
}

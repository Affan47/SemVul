setFieldOffset(AggregateDeclaration *ad, unsigned *poffset, bool isunion)
{
    Dsymbols *d = include(NULL, NULL);

    if (d)
    {
        for (size_t i = 0; i < d->dim; i++)
        {   Dsymbol *s = (*d)[i];
            s->setFieldOffset(ad, poffset, isunion);
        }
    }
}

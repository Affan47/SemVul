FindVariable(VARSTORE *varstore, const char *name)
{
    VARIABLE *ptr;

    assert(varstore != NULL);
    assert(name != NULL);

#if DEBUG
    variableLookups++;
#endif

    do {
        ptr = VariableSplay(name, &varstore->root);
        if(ptr)
            return ptr;


        varstore = varstore->parent;
    } while (varstore != NULL);

    return NULL;
}

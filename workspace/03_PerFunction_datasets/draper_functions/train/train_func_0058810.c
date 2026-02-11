ensRegistryAliasAdd(const AjPStr species, const AjPStr alias)
{
    AjBool debug = AJFALSE;

    AjPStr current = NULL;

    debug = ajDebugTest("ensRegistryAliasAdd");

    if (debug)
        ajDebug("ensRegistryAliasAdd\n"
                "  species '%S'\n"
                "  alias '%S'\n",
                species,
                alias);

    if (!species)
        return ajFalse;

    if (!alias)
        return ajFalse;

    current = (AjPStr) ajTableFetchmodV(registryGAlias, (const void *) alias);

    if (current)
    {
        if (ajStrMatchCaseS(current, species))
        {
            if (debug)
                ajDebug("ensRegistryAliasAdd has already added alias '%S' for "
                        "this species '%S'.\n", alias, current);

            return ajTrue;
        }
        else
        {
            if (debug)
                ajDebug("ensRegistryAliasAdd has already added alias '%S' for "
                        "a different species '%S'.\n", alias, current);

            return ajFalse;
        }
    }

    ajTablePut(registryGAlias,
               (void *) ajStrNewS(alias),
               (void *) ajStrNewS(species));

    if (debug)
        ajDebug("ensRegistryAliasAdd added alias '%S' for species '%S'.\n",
                alias, species);

    return ajTrue;
}

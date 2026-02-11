ensFeatureadaptorSetTablenames(EnsPFeatureadaptor fa,
                                      const char* const* Ptablenames)
{
    register ajuint i = 0U;

    EnsPDatabaseadaptor dba = NULL;

    if (!fa)
        return ajFalse;

    if (!Ptablenames)
        return ajFalse;

    dba = ensFeatureadaptorGetDatabaseadaptor(fa);

    if (!dba)
        return ajFalse;

    if (ensDatabaseadaptorGetMultispecies(dba))
    {


        if (fa->Tablenames)
        {
            for (i = 0U; fa->Tablenames[i]; i++)
                ajCharDel(&fa->Tablenames[i]);

            AJFREE(fa->Tablenames);
        }


        for (i = 0U; Ptablenames[i]; i++);

        fa->Tablenames = AJCALLOC0(i + 1U + 2U, sizeof (char *));

        for (i = 0U; Ptablenames[i]; i++)
            fa->Tablenames[i] = ajCharNewC(Ptablenames[i]);

        fa->Tablenames[i] = ajCharNewC("seq_region");
        i++;
        fa->Tablenames[i] = ajCharNewC("coord_system");
        i++;
        fa->Tablenames[i] = NULL;

        Ptablenames = (const char* const *) fa->Tablenames;
    }

    return ensBaseadaptorSetTablenames(
        ensFeatureadaptorGetBaseadaptor(fa),
        Ptablenames);
}

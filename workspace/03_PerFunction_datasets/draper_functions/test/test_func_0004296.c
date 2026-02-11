freeEra(Census *census)
{
    if (RtsFlags.ProfFlags.bioSelector != NULL)

    {
        arenaFree(census->arena);
        freeHashTable(census->hash, NULL);
    }
}

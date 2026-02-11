FreeMPQSearch(TMPQSearch *& hs)
{
    if(hs != NULL)
    {
        if(hs->pSearchTable != NULL)
            FREEMEM(hs->pSearchTable);
        FREEMEM(hs);
        hs = NULL;
    }
}

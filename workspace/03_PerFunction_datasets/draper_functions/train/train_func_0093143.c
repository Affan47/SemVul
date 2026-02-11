delete_all_entries()
{
    CVmHashEntry **tableptr;
    size_t i;

    for (tableptr = table_, i = 0 ; i < table_size_ ; ++i, ++tableptr)
    {
        CVmHashEntry *entry;
        CVmHashEntry *nxt;


        for (entry = *tableptr ; entry ; entry = nxt)
        {

            nxt = entry->nxt_;


            delete entry;
        }


        *tableptr = 0;
    }
}

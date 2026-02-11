TrGetNextNode (
    void)
{

    if (Gbl_NodeCacheNext >= Gbl_NodeCacheLast)
    {
        Gbl_NodeCacheNext = UtLocalCalloc (sizeof (ACPI_PARSE_OBJECT) *
                                ASL_NODE_CACHE_SIZE);
        Gbl_NodeCacheLast = Gbl_NodeCacheNext + ASL_NODE_CACHE_SIZE;
    }

    return (Gbl_NodeCacheNext++);
}

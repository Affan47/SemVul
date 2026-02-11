TrLinkPeerNodes (
    UINT32                  NumPeers,
    ...)
{
    ACPI_PARSE_OBJECT       *This;
    ACPI_PARSE_OBJECT       *Next;
    va_list                 ap;
    UINT32                  i;
    ACPI_PARSE_OBJECT       *Start;


    DbgPrint (ASL_PARSE_OUTPUT,
        "\nLinkPeerNodes: (%u) ", NumPeers);

    va_start (ap, NumPeers);
    This = va_arg (ap, ACPI_PARSE_OBJECT *);
    Start = This;


    for (i = 0; i < (NumPeers -1); i++)
    {
        DbgPrint (ASL_PARSE_OUTPUT, "%u=%p ", (i+1), This);

        while (This->Asl.Next)
        {
            This = This->Asl.Next;
        }


        Next = va_arg (ap, ACPI_PARSE_OBJECT *);
        if (!Next)
        {
            Next = TrAllocateNode (PARSEOP_DEFAULT_ARG);
        }


        This->Asl.Next = Next;
        This = Next;
    }
    va_end (ap);

    DbgPrint (ASL_PARSE_OUTPUT,"\n\n");
    return (Start);
}

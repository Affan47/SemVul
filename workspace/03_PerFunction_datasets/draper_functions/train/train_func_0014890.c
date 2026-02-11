LsEmitOffsetTableEntry (
    UINT32                  FileId,
    ACPI_NAMESPACE_NODE     *Node,
    UINT32                  NamepathOffset,
    UINT32                  Offset,
    char                    *OpName,
    UINT64                  Value,
    UINT8                   AmlOpcode,
    UINT16                  ParentOpcode)
{
    ACPI_BUFFER             TargetPath;
    ACPI_STATUS             Status;


    TargetPath.Length = ACPI_ALLOCATE_LOCAL_BUFFER;
    Status = AcpiNsHandleToPathname (Node, &TargetPath);
    if (ACPI_FAILURE (Status))
    {
        return;
    }


    strcpy (MsgBuffer, "\"");
    strcat (MsgBuffer, &((char *) TargetPath.Pointer)[1]);
    strcat (MsgBuffer, "\",");
    ACPI_FREE (TargetPath.Pointer);


    FlPrintFile (FileId,
        "    {%-29s 0x%4.4X, 0x%8.8X, 0x%2.2X, 0x%8.8X, 0x%8.8X%8.8X}, /* %s */\n",
        MsgBuffer, ParentOpcode, NamepathOffset, AmlOpcode,
        Offset, ACPI_FORMAT_UINT64 (Value), OpName);
}

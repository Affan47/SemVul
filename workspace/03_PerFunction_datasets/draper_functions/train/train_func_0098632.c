ReadDataBlocks(PCFFOLDER_NODE FolderNode)


{
    ULONG AbsoluteOffset;
    ULONG UncompOffset;
    PCFDATA_NODE Node;
    ULONG BytesRead;
    ULONG Status;
    ULONG i;

    DPRINT(MAX_TRACE, ("Reading data blocks for folder (%u)  at absolute offset (0x%X).\n",
        (UINT)FolderNode->Index, (UINT)FolderNode->Folder.DataOffset));

    AbsoluteOffset = FolderNode->Folder.DataOffset;
    UncompOffset   = FolderNode->UncompOffset;

    for (i = 0; i < FolderNode->Folder.DataBlockCount; i++)
    {
        Node = NewDataNode(FolderNode);
        if (!Node)
        {
            DPRINT(MIN_TRACE, ("Insufficient memory.\n"));
            return CAB_STATUS_NOMEMORY;
        }


#if defined(_WIN32)
        if( SetFilePointer(FileHandle,
                           AbsoluteOffset,
                           NULL,
                           FILE_BEGIN) == INVALID_SET_FILE_POINTER )
        {
            DPRINT(MIN_TRACE, ("SetFilePointer() failed, error code is %u.\n", (UINT)GetLastError()));
            return CAB_STATUS_INVALID_CAB;
        }
#else
        if (fseek(FileHandle, (off_t)AbsoluteOffset, SEEK_SET) != 0)
        {
            DPRINT(MIN_TRACE, ("fseek() failed.\n"));
            return CAB_STATUS_INVALID_CAB;
        }
#endif

        if ((Status = ReadBlock(&Node->Data, sizeof(CFDATA),
            &BytesRead)) != CAB_STATUS_SUCCESS)
        {
            DPRINT(MIN_TRACE, ("Cannot read from file (%u).\n", (UINT)Status));
            return CAB_STATUS_INVALID_CAB;
        }

        DPRINT(MAX_TRACE, ("AbsOffset (0x%X)  UncompOffset (0x%X)  Checksum (0x%X)  CompSize (%u)  UncompSize (%u).\n",
            (UINT)AbsoluteOffset,
            (UINT)UncompOffset,
            (UINT)Node->Data.Checksum,
            Node->Data.CompSize,
            Node->Data.UncompSize));

        Node->AbsoluteOffset = AbsoluteOffset;
        Node->UncompOffset   = UncompOffset;

        AbsoluteOffset += sizeof(CFDATA) + Node->Data.CompSize;
        UncompOffset   += Node->Data.UncompSize;
    }

    FolderUncompSize = UncompOffset;

    return CAB_STATUS_SUCCESS;
}

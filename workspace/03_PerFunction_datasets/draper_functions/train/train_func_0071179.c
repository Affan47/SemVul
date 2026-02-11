HvLoadHive(IN PHHIVE Hive,
           IN ULONG FileSize)
{
    PHBASE_BLOCK BaseBlock = NULL;
    ULONG Result;
    LARGE_INTEGER TimeStamp;
    ULONG Offset = 0;
    PVOID HiveData;


    Result = HvpGetHiveHeader(Hive, &BaseBlock, &TimeStamp);
    switch (Result)
    {

        case NoMemory:


            return STATUS_INSUFFICIENT_RESOURCES;


        case NotHive:


            return STATUS_NOT_REGISTRY_FILE;


        case RecoverData:
        case RecoverHeader:


            return STATUS_REGISTRY_CORRUPT;
    }


    BaseBlock->BootType = 0;


    Hive->BaseBlock = BaseBlock;
    Hive->Version = Hive->BaseBlock->Minor;


    HiveData = Hive->Allocate(FileSize, TRUE, TAG_CM);
    if (!HiveData) return STATUS_INSUFFICIENT_RESOURCES;


    Result = Hive->FileRead(Hive,
                            HFILE_TYPE_PRIMARY,
                            &Offset,
                            HiveData,
                            FileSize);
    if (!Result) return STATUS_NOT_REGISTRY_FILE;


    ((PHBASE_BLOCK)HiveData)->Length = FileSize;


    Hive->Free(BaseBlock, 0);


    return HvpInitializeMemoryHive(Hive, HiveData);
}

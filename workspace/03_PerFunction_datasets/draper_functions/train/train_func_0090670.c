initCompiler (size_t size)
{
    static BlockHeader dummyHeader;
    gBlockHeader = &dummyHeader;


    assert (sizeof(HashNode) <= sizeof(PatchNode));


    sBuffer = malloc (size);
    if (sBuffer == NULL)
        fatalError ("Couldn't allocate code cache");

    memset (sBuffer, 0, size);
    sBufferSize = size / 4;


    gHashSize = 1;
    while (gHashSize < (sBufferSize / 20))
        gHashSize *= 2;


    gHashTable = (HashNode**) sBuffer;

    sCodeStart = sCodeTop = (Block) (gHashTable + gHashSize);
    sTempStart = sTempEnd = (PatchNode*) (sBuffer + sBufferSize);
}

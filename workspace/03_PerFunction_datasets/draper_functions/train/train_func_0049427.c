freeFileResources(InFileStream* filePtr)
{
    if(filePtr != 0)
    {
        filePtr->close();
        delete filePtr;
        filePtr = 0;
    }
}

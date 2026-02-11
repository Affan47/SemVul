resetWriteStatus(BkHardLink* fileLocations)
{
    BkHardLink* currentNode;

    currentNode = fileLocations;
    while(currentNode != NULL)
    {
        currentNode->extentNumberWrittenTo = 0;

        currentNode = currentNode->next;
    }
}

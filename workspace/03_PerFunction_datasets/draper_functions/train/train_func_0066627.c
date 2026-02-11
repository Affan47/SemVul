Keccak_ParallelDuplexGetTotalInputIndex(Keccak_ParallelDuplexInstances *instances)
{
    unsigned int totalInputIndex = 0;
    unsigned int i;

    for(i=0; i<NumberOfParallelInstances; i++)
        totalInputIndex += instances->byteInputIndex[i];
    return totalInputIndex;
}

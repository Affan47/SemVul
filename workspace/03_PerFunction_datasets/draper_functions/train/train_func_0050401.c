KeccakF_ParallelStateExtractLanesAll(const void *states, unsigned char *data, unsigned int laneCount)
{
    unsigned int i;

    for(i=0; i<NumberOfParallelInstances; i++) {
        KeccakF_StateExtractLanes(stateWithIndex(i), data, laneCount);
        data += laneCount*KeccakF_laneInBytes;
    }
}

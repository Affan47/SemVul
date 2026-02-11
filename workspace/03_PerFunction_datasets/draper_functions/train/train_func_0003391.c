Keccak_ParallelDuplexingOverwriteWithZeroes(Keccak_ParallelDuplexInstances *instances, unsigned int instanceIndex, unsigned int inByteLen)
{
    const unsigned int rho_max = instances->rate - 2;
    unsigned int i;

    if (instanceIndex >= NumberOfParallelInstances)
        return 1;
    if (instances->byteInputIndex[instanceIndex] != 0)
        return 1;
    if (inByteLen*8 > rho_max)
        return 1;

    KeccakF_ParallelStateOverwriteWithZeroes(instances->states, instanceIndex, inByteLen);
    instances->byteInputIndex[instanceIndex] += inByteLen;

    return 0;
}

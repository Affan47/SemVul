fromBytesToWords(tKeccakLane *stateAsWords, const unsigned char *state)
{
    unsigned int i, j;

    for(i=0; i<nrLanes; i++) {
        stateAsWords[i] = 0;
        for(j=0; j<(64/8); j++)
            stateAsWords[i] |= (tKeccakLane)(state[i*(64/8)+j]) << (8*j);
    }
}

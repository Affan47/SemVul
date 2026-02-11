mem_openmem(void **buffptr,
                size_t *buffsize,
                size_t deltasize,
                void *(*memrealloc)(void *p, size_t newsize),
                int *handle)


{
    int ii;

    *handle = -1;
    for (ii = 0; ii < NMAXFILES; ii++)
    {
        if (memTable[ii].memaddrptr == 0)
        {
            *handle = ii;
            break;
        }
    }
    if (*handle == -1)
       return(TOO_MANY_FILES);

    memTable[ii].memaddrptr = (char **) buffptr;
    memTable[ii].memsizeptr = buffsize;
    memTable[ii].deltasize = deltasize;
    memTable[ii].fitsfilesize = *buffsize;
    memTable[ii].currentpos = 0;
    memTable[ii].mem_realloc = memrealloc;
    return(0);
}

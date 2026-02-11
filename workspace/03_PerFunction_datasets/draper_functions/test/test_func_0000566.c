mem_truncate(int handle, LONGLONG filesize)


{
    char *ptr;


    if ( memTable[handle].mem_realloc )
    {
        ptr = (memTable[handle].mem_realloc)(
                                *(memTable[handle].memaddrptr),
                                 (size_t) filesize);
        if (!ptr)
        {
            ffpmsg("Failed to reallocate memory (mem_truncate)");
            return(MEMORY_ALLOCATION);
        }


        if ( filesize > *(memTable[handle].memsizeptr) )
        {
             memset(ptr + *(memTable[handle].memsizeptr),
                    0,
                ((size_t) filesize) - *(memTable[handle].memsizeptr) );
        }

        *(memTable[handle].memaddrptr) = ptr;
        *(memTable[handle].memsizeptr) = (size_t) (filesize);
    }

    memTable[handle].currentpos = filesize;
    memTable[handle].fitsfilesize = filesize;
    return(0);
}

file_flush(int handle)


{
    if (fflush(handleTable[handle].fileptr) )
        return(WRITE_ERROR);


#if MACHINE == IBMPC

    if (file_seek(handle, handleTable[handle].currentpos))
            return(SEEK_ERROR);

#endif

    return(0);
}

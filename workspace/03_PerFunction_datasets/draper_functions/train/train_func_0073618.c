SFILEfileno(SFILE *SF)
{
    struct sfile *sf = (struct sfile *)SF;

    if (sf->type == SFILE_FDESC || sf->type == SFILE_FPTR)
	return sf->fd;
#if defined(HANDLE_SOCKET)
    else if (sf->type == SFILE_SOCKET)
	return sf->socket;
#endif
    else
    {
	fprintf(stderr, "unknown SFILE type\n");
	abort();
    }
    return -1;
}
